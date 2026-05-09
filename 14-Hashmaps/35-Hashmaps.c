#include "29-AutomatedTesting_Framework.h"
#include "35-Hashmaps_Library.h"
#include <assert.h>
#include "34-bstrlib.h"

Hashmap *map = NULL;
static int traverse_called = 0;

static int traverse_test_cb(HashmapNode *node)
{
    debug("KEY: %s", bdata((bstring) node->key));
    traverse_called++;
    return 0;
}

static int encrypt_cb(HashmapNode *node)
{
    bstring value = (bstring) node->data;
    bstring key = (bstring) node->key;
    debug("ENCRYPT: %s -> %s", bdata(key), bdata(value));
    return 0;
}

char *test_create()
{
    map = Hashmap_create(NULL, NULL);
    mu_assert(map != NULL, "Failed to create map.");
    return NULL;
}

char *test_destroy()
{
    Hashmap_destroy(map);
    return NULL;
}

char *test_get_set()
{
    bstring test1 = bfromcstr("test data 1");
    bstring test2 = bfromcstr("test data 2");
    bstring test3 = bfromcstr("xData");
    bstring expect1 = bfromcstr("the value 1");
    bstring expect2 = bfromcstr("the value 2");
    bstring expect3 = bfromcstr("value 3");

    int rc = Hashmap_set(map, test1, expect1);
    mu_assert(rc == 0, "Failed to set test1");
    bstring result = Hashmap_get(map, test1);
    mu_assert(result == expect1, "Wrong value for test1.");

    rc = Hashmap_set(map, test2, expect2);
    mu_assert(rc == 0, "Failed to set test2");
    result = Hashmap_get(map, test2);
    mu_assert(result == expect2, "Wrong value for test2.");

    rc = Hashmap_set(map, test3, expect3);
    mu_assert(rc == 0, "Failed to set test3");
    result = Hashmap_get(map, test3);
    mu_assert(result == expect3, "Wrong value for test3.");

    return NULL;
}

char *test_traverse()
{
    int rc = Hashmap_traverse(map, traverse_test_cb);
    mu_assert(rc == 0, "Traverse failed.");
    mu_assert(traverse_called == 3, "Wrong count traverse.");

    traverse_called = 0;
    rc = Hashmap_traverse(map, encrypt_cb);
    mu_assert(rc == 0, "Traverse failed.");

    return NULL;
}

char *test_delete()
{
    bstring test1 = bfromcstr("test data 1");
    bstring test2 = bfromcstr("test data 2");
    bstring test3 = bfromcstr("xData");

    bstring deleted = (bstring) Hashmap_delete(map, test1);
    mu_assert(deleted != NULL, "Should get a value.");
    bstring result = Hashmap_get(map, test1);
    mu_assert(result == NULL, "Should delete.");
    bdestroy(deleted);

    deleted = (bstring) Hashmap_delete(map, test2);
    mu_assert(deleted != NULL, "Should get a value.");
    result = Hashmap_get(map, test2);
    mu_assert(result == NULL, "Should delete.");
    bdestroy(deleted);

    deleted = (bstring) Hashmap_delete(map, test3);
    mu_assert(deleted != NULL, "Should get a value.");
    result = Hashmap_get(map, test3);
    mu_assert(result == NULL, "Should delete.");
    bdestroy(deleted);

    bdestroy(test1);
    bdestroy(test2);
    bdestroy(test3);

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
