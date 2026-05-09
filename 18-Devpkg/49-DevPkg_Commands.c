#include <apr_uri.h>
#include <apr_fnmatch.h>
#include <unistd.h>
#include "49-DevPkg_Commands.h"
#include "18-DebugMacros.h"
#include "34-bstrlib.h"
#include "46-DevPkg_DB.h"
#include "47-DevPkg_Shell.h"

int Command_fetch(apr_pool_t *p, const char *url, int fetch_only)
{
    apr_uri_t info = {.port = 0};
    int rc = 0;
    const char *depends_file = NULL;
    apr_status_t rv = apr_uri_parse(p, url, &info);

    check(rv == APR_SUCCESS, "Failed to parse URL: %s", url);

    if (apr_fnmatch("*.git", url, 0) == APR_SUCCESS) {
        rc = Shell_exec(GIT_SH, "URL", url, NULL);
        check(rc == 0, "Git failed.");
    } else if (apr_fnmatch("*.tar.gz", url, 0) == APR_SUCCESS) {
        rc = Shell_exec(CURL_SH, "URL", url, "TARGET", TAR_GZ_SRC, NULL);
        check(rc == 0, "Curl failed.");
        rv = apr_dir_make_recursive(BUILD_DIR, APR_UREAD | APR_UWRITE | APR_UEXECUTE, p);
        check(rv == APR_SUCCESS, "Failed to make build dir %s", BUILD_DIR);
        rc = Shell_exec(TAR_SH, "FILE", TAR_GZ_SRC, NULL);
        check(rc == 0, "Failed to untar %s", TAR_GZ_SRC);
    } else if (apr_fnmatch("*.tar.bz2", url, 0) == APR_SUCCESS) {
        rc = Shell_exec(CURL_SH, "URL", url, "TARGET", TAR_BZ2_SRC, NULL);
        check(rc == 0, "Curl failed.");
        rv = apr_dir_make_recursive(BUILD_DIR, APR_UREAD | APR_UWRITE | APR_UEXECUTE, p);
        check(rv == APR_SUCCESS, "Failed to make build dir %s", BUILD_DIR);
        rc = Shell_exec(TAR_SH, "FILE", TAR_BZ2_SRC, NULL);
        check(rc == 0, "Failed to untar %s", TAR_BZ2_SRC);
    } else {
        sentinel("Don't know how to handle %s", url);
    }

    // always look for a DEPENDS file
    depends_file = apr_psprintf(p, "%s/DEPENDS", BUILD_DIR);
    if (access(depends_file, R_OK) == 0) {
        log_info("I see a DEPENDS file: %s", depends_file);
        rc = Command_depends(p, depends_file);
        check(rc == 0, "Failed to process depends: %s", depends_file);
    }

    return 0;

error:
    return -1;
}

int Command_build(apr_pool_t *p, const char *url, const char *configure_opts, const char *make_opts, const char *install_opts)
{
    int rc = 0;

    if (access(BUILD_DIR, R_OK | X_OK) == -1) {
        rc = Command_fetch(p, url, 0);
        check(rc == 0, "Failed to fetch: %s", url);
    }

    if (access(apr_psprintf(p, "%s/configure", BUILD_DIR), X_OK) == 0) {
        log_info("Has a configure script, running it.");
        rc = Shell_exec(CONFIGURE_SH, "OPTS", configure_opts, NULL);
        check(rc == 0, "Failed to configure.");
    }

    rc = Shell_exec(MAKE_SH, "OPTS", make_opts, NULL);
    check(rc == 0, "Failed to make.");

    rc = Shell_exec(INSTALL_SH, "TARGET", install_opts ? install_opts : "install", NULL);
    check(rc == 0, "Failed to install.");

    rc = Shell_exec(CLEANUP_SH, NULL);
    check(rc == 0, "Failed to cleanup.");

    rc = DB_update(url);
    check(rc == 0, "Failed to add to database.");

    return 0;

error:
    return -1;
}

int Command_install(apr_pool_t *p, const char *url, const char *configure_opts, const char *make_opts, const char *install_opts)
{
    int rc = DB_find(url);
    check(rc != -1, "Error checking the database.");

    if (rc == 1) {
        log_info("Package %s already installed.", url);
        return 0;
    }

    rc = Command_build(p, url, configure_opts, make_opts, install_opts);
    check(rc == 0, "Failed to install package.");

    return 0;

error:
    return -1;
}

int Command_depends(apr_pool_t *p, const char *path)
{
    FILE *in = fopen(path, "r");
    check(in != NULL, "Failed to open depends file: %s", path);
    bstring line = NULL;

    while ((line = bgets((bNgetc) fgetc, in, '\n')) != NULL) {
        btrimws(line);
        log_info("Processing dependency: %s", bdata(line));
        int rc = Command_install(p, bdata(line), NULL, NULL, NULL);
        check(rc == 0, "Failed to install dependency: %s", bdata(line));
        bdestroy(line);
    }

    fclose(in);
    return 0;

error:
    if (in) fclose(in);
    return -1;
}
