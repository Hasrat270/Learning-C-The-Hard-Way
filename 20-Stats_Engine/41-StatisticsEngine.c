#include "29-AutomatedTesting_Framework.h"
#include "41-StatisticsEngine_Library.h"
#include <math.h>

char *test_operations()
{
    Stats *st = Stats_create();
    mu_assert(st != NULL, "Failed to create stats.");

    Stats_sample(st, 1.0);
    Stats_sample(st, 2.0);
    Stats_sample(st, 3.0);

    mu_assert(st->n == 3, "Wrong count.");
    mu_assert(st->sum == 6.0, "Wrong sum.");
    mu_assert(st->min == 1.0, "Wrong min.");
    mu_assert(st->max == 3.0, "Wrong max.");
    mu_assert(Stats_mean(st) == 2.0, "Wrong mean.");
    mu_assert(Stats_stddev(st) == 1.0, "Wrong stddev.");

    Stats_dump(st);
    free(st);

    return NULL;
}

char *all_tests()
{
    mu_suite_start();
    mu_run_test(test_operations);
    return NULL;
}

RUN_TESTS(all_tests);
