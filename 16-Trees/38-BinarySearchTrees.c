#include "29-AutomatedTesting_Framework.h"
#include "38-BinarySearchTrees_Library.h"
#include <assert.h>
#include "34-bstrlib.h"

BSTree *map = NULL;
static int traverse_called = 0;

struct tagbstring test1 = { -1, 11, (unsigned char *) "test data 1" };
struct tagbstring test2 = { -1, 11, (unsigned char *) "test data 2" };
struct tagbstring test3 = { -1, 5, (unsigned char *) "xData" };
struct tagbstring expect1 = { -1, 11, (unsigned char *) "the value 1" };
struct tagbstring expect2 = { -1, 11, (unsigned char *) "the value 2" };
struct tagbstring expect3 = { -1, 7, (unsigned char *) "value 3" };

static int traverse_test_cb(BSTreeNode *node)
{
    debug("KEY: %s", bdata((bstring) node->key));
    traverse_called++;
    return 0;
}

char *test_create()
{
    map = BSTree_create(NULL);
    mu_assert(map != NULL, "Failed to create map.");
    return NULL;
}

char *test_destroy()
{
    BSTree_destroy(map);
    return NULL;
}

char *test_get_set()
{
    int rc = BSTree_set(map, &test1, &expect1);
    mu_assert(rc == 0, "Failed to set &test1");
    bstring result = BSTree_get(map, &test1);
    mu_assert(result == &expect1, "Wrong value for test1.");

    rc = BSTree_set(map, &test2, &expect2);
    mu_assert(rc == 0, "Failed to set test2");
    result = BSTree_get(map, &test2);
    mu_assert(result == &expect2, "Wrong value for test2.");

    rc = BSTree_set(map, &test3, &expect3);
    mu_assert(rc == 0, "Failed to set test3");
    result = BSTree_get(map, &test3);
    mu_assert(result == &expect3, "Wrong value for test3.");

    return NULL;
}

char *test_traverse()
{
    int rc = BSTree_traverse(map, traverse_test_cb);
    mu_assert(rc == 0, "Traverse failed.");
    mu_assert(traverse_called == 3, "Wrong count traverse.");

    return NULL;
}

char *test_delete()
{
    bstring deleted = (bstring) BSTree_delete(map, &test1);
    mu_assert(deleted != NULL, "Should get a value.");
    bstring result = BSTree_get(map, &test1);
    mu_assert(result == NULL, "Should delete.");

    deleted = (bstring) BSTree_delete(map, &test2);
    mu_assert(deleted != NULL, "Should get a value.");
    result = BSTree_get(map, &test2);
    mu_assert(result == NULL, "Should delete.");

    deleted = (bstring) BSTree_delete(map, &test3);
    mu_assert(deleted != NULL, "Should get a value.");
    result = BSTree_get(map, &test3);
    mu_assert(result == NULL, "Should delete.");

    return NULL;
}

char *all_tests()
{
    mu_suite_start();

    mu_run_test(test_create);
    mu_run_test(test_get_set);
    mu_run_test(test_traverse);
    mu_run_test(test_delete);
    mu_run_test(test_destroy);

    return NULL;
}

RUN_TESTS(all_tests);
