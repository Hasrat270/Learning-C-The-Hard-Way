#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <glob.h>
#include "18-DebugMacros.h"

#define MAX_LINE 1024

int list_files(char *list[], int max_files)
{
    FILE *f = fopen(".logfind", "r");
    if (!f) {
        // Fallback to home directory if local .logfind not found
        char *home = getenv("HOME");
        char path[MAX_LINE];
        snprintf(path, MAX_LINE, "%s/.logfind", home);
        f = fopen(path, "r");
    }
    
    check(f, "Could not find .logfind file in current or home directory.");

    int count = 0;
    char line[MAX_LINE];

    while (fgets(line, MAX_LINE, f) && count < max_files) {
        line[strcspn(line, "\n")] = '\0'; // Remove newline
        list[count] = strdup(line);
        count++;
    }

    fclose(f);
    return count;

error:
    if (f) fclose(f);
    return -1;
}

int scan_file(const char *filename, int argc, char *argv[], int use_or)
{
    FILE *f = fopen(filename, "r");
    check(f, "Failed to open file: %s", filename);

    char line[MAX_LINE];
    int found_any = 0;

    while (fgets(line, MAX_LINE, f)) {
        int matches = 0;
        for (int i = 0; i < argc; i++) {
            if (strstr(line, argv[i])) {
                matches++;
            }
        }

        if (use_or) {
            if (matches > 0) {
                printf("%s: %s", filename, line);
                found_any = 1;
            }
        } else {
            if (matches == argc) {
                printf("%s: %s", filename, line);
                found_any = 1;
            }
        }
    }

    fclose(f);
    return found_any;

error:
    if (f) fclose(f);
    return -1;
}

int main(int argc, char *argv[])
{
    check(argc >= 2, "USAGE: logfind [-o] words...");

    int use_or = 0;
    int start_arg = 1;

    if (strcmp(argv[1], "-o") == 0) {
        use_or = 1;
        start_arg = 2;
        check(argc >= 3, "USAGE: logfind [-o] words...");
    }

    char *patterns[100];
    int file_count = list_files(patterns, 100);
    check(file_count > 0, "No files found in .logfind");

    for (int i = 0; i < file_count; i++) {
        glob_t glob_results;
        int rc = glob(patterns[i], GLOB_NOCHECK | GLOB_TILDE, NULL, &glob_results);
        
        if (rc == 0) {
            for (size_t j = 0; j < glob_results.gl_pathc; j++) {
                scan_file(glob_results.gl_pathv[j], argc - start_arg, &argv[start_arg], use_or);
            }
        }
        globfree(&glob_results);
        free(patterns[i]);
    }

    return 0;

error:
    return 1;
}
