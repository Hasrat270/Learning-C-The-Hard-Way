#include "29-AutomatedTesting_Framework.h"
#include "37-StringAlgorithms_Library.h"
#include "34-bstrlib.h"
#include <time.h>

struct tagbstring IN_STR = { -1, 11, (unsigned char *) "hello world" };
struct tagbstring ALPHA = { -1, 5, (unsigned char *) "world" };
struct tagbstring BETA = { -1, 5, (unsigned char *) "hello" };
struct tagbstring GAMMA = { -1, 1, (unsigned char *) "o" };

char *test_find()
{
    int found_at = String_find(&IN_STR, &ALPHA);
    mu_assert(found_at == 6, "Failed to find 'world' at 6");

    found_at = String_find(&IN_STR, &BETA);
    mu_assert(found_at == 0, "Failed to find 'hello' at 0");

    found_at = String_find(&IN_STR, &GAMMA);
    mu_assert(found_at == 4, "Failed to find 'o' at 4");

    return NULL;
}

char *test_scanner()
{
    StringScanner *scan = StringScanner_create(&IN_STR);
    mu_assert(scan != NULL, "Failed to create scanner.");

    int found_at = StringScanner_scan(scan, &GAMMA);
    mu_assert(found_at == 4, "Failed to find 'o' at 4 with scanner");

    found_at = StringScanner_scan(scan, &GAMMA);
    mu_assert(found_at == 7, "Failed to find 'o' at 7 with scanner");

    found_at = StringScanner_scan(scan, &GAMMA);
    mu_assert(found_at == -1, "Should not find more 'o'");

    StringScanner_destroy(scan);

    return NULL;
}

char *all_tests()
{
    mu_suite_start();

    mu_run_test(test_find);
    mu_run_test(test_scanner);

    return NULL;
}

RUN_TESTS(all_tests);
