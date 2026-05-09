#include "29-AutomatedTesting_Framework.h"
#include "44-TernarySearchTrees_Library.h"
#include <string.h>
#include <assert.h>
#include "34-bstrlib.h"

TSTree *node = NULL;
char *valueA = "VALUEA";
char *valueB = "VALUEB";
char *valueC = "VALUEC";
char *reverse = "ESREVER";

char *test_insert()
{
    node = TSTree_insert(node, "apple", 5, valueA);
    mu_assert(node != NULL, "Failed to insert apple.");

    node = TSTree_insert(node, "apply", 5, valueB);
    mu_assert(node != NULL, "Failed to insert apply.");

    node = TSTree_insert(node, "banana", 6, valueC);
    mu_assert(node != NULL, "Failed to insert banana.");

    return NULL;
}

char *test_search_exact()
{
    char *res = TSTree_search(node, "apple", 5);
    mu_assert(res == valueA, "Got wrong value for apple.");

    res = TSTree_search(node, "apply", 5);
    mu_assert(res == valueB, "Got wrong value for apply.");

    res = TSTree_search(node, "banana", 6);
    mu_assert(res == valueC, "Got wrong value for banana.");

    res = TSTree_search(node, "app", 3);
    mu_assert(res == NULL, "Should not find app (exact).");

    return NULL;
}

char *test_search_prefix()
{
    char *res = TSTree_search_prefix(node, "apple", 5);
    mu_assert(res == valueA, "Got wrong value for apple prefix.");

    res = TSTree_search_prefix(node, "app", 3);
    mu_assert(res == valueA, "Got wrong value for app prefix.");

    res = TSTree_search_prefix(node, "ban", 3);
    mu_assert(res == valueC, "Got wrong value for ban prefix.");

    return NULL;
}

char *test_traverse()
{
    // Just testing it doesn't crash for now
    TSTree_traverse(node, NULL, NULL);
    return NULL;
}

char *test_destroy()
{
    TSTree_destroy(node);
    return NULL;
}

char *all_tests()
{
    mu_suite_start();

    mu_run_test(test_insert);
    mu_run_test(test_search_exact);
    mu_run_test(test_search_prefix);
    mu_run_test(test_traverse);
    mu_run_test(test_destroy);

    return NULL;
}

RUN_TESTS(all_tests);
