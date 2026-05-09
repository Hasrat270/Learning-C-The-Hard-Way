#include "29-AutomatedTesting_Framework.h"
#include "42-RingBuffer_Library.h"
#include <string.h>

char *test_create()
{
    RingBuffer *buffer = RingBuffer_create(10);
    mu_assert(buffer != NULL, "Failed to create ringbuffer.");
    RingBuffer_destroy(buffer);
    return NULL;
}

char *test_read_write()
{
    RingBuffer *buffer = RingBuffer_create(10);
    char *data = "hello";
    int rc = RingBuffer_write(buffer, data, 5);
    mu_assert(rc == 5, "Failed to write 5 bytes.");
    mu_assert(RingBuffer_available_data(buffer) == 5, "Should have 5 bytes.");

    char target[6] = {0};
    rc = RingBuffer_read(buffer, target, 5);
    mu_assert(rc == 5, "Failed to read 5 bytes.");
    mu_assert(strcmp(target, "hello") == 0, "Read wrong data.");
    mu_assert(RingBuffer_available_data(buffer) == 0, "Should be empty.");

    RingBuffer_destroy(buffer);
    return NULL;
}

char *all_tests()
{
    mu_suite_start();

    mu_run_test(test_create);
    mu_run_test(test_read_write);

    return NULL;
}

RUN_TESTS(all_tests);
