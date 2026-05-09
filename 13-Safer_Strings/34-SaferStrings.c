#include "29-AutomatedTesting_Framework.h"
#include "34-bstrlib.h"

char *test_bfromcstr()
{
    bstring s = bfromcstr("Hello World");
    mu_assert(s != NULL, "Failed to create bstring from cstr.");
    mu_assert(blength(s) == 11, "Wrong length.");
    mu_assert(strcmp(bdata(s), "Hello World") == 0, "Wrong data content.");
    bdestroy(s);
    return NULL;
}

char *test_bstrcpy()
{
    bstring s1 = bfromcstr("Test Copy");
    bstring s2 = bstrcpy(s1);
    mu_assert(s2 != NULL, "Failed to copy bstring.");
    mu_assert(biseq(s1, s2), "Strings are not equal after copy.");
    bdestroy(s1);
    bdestroy(s2);
    return NULL;
}

char *test_bassigncstr()
{
    bstring s = bfromcstr("Old Value");
    bassigncstr(s, "New Value");
    mu_assert(strcmp(bdata(s), "New Value") == 0, "Assign cstr failed.");
    bdestroy(s);
    return NULL;
}

char *test_bconcat()
{
    bstring s1 = bfromcstr("Hello ");
    bstring s2 = bfromcstr("World");
    bconcat(s1, s2);
    mu_assert(strcmp(bdata(s1), "Hello World") == 0, "Concat failed.");
    bdestroy(s1);
    bdestroy(s2);
    return NULL;
}

char *all_tests()
{
    mu_suite_start();

    mu_run_test(test_bfromcstr);
    mu_run_test(test_bstrcpy);
    mu_run_test(test_bassigncstr);
    mu_run_test(test_bconcat);

    return NULL;
}

RUN_TESTS(all_tests);
