#include "tests.h"
#include "file.h"
#include "free.h"
#include <stdio.h>
#include <stdlib.h>

// Test variables
struct file *empty_file;
struct file *test_file;
struct element *e1;
struct element *e2;
struct element *e3;

// Set up empty and non-empty files
static void setup(void) {
    empty_file = file_init();
    test_file = file_init();
    e1 = create_element();
    e2 = create_element();
    e3 = create_element();
    push(test_file, e1);
    push(test_file, e2);
    push(test_file, e3);
}

static void teardown(void) {
    free_file(empty_file);
    free_file(test_file);
}

// Test the file initialization
void test_init(void) {
    printf("%s", __func__);

    struct file* file = file_init();

    if (number_of_element_file(file) != 0)
        FAIL("File initialization failed");

    free_file(file);
}

// Test pushing elements into the file
void test_push(void) {
    printf("%s", __func__);

    struct element *e4 = create_element();
    struct element *e5 = create_element();
    struct element *e6 = create_element();
    push(empty_file, e4);
    push(empty_file, e5);
    push(empty_file, e6);

    if (number_of_element_file(empty_file) != 3)
        FAIL("Pushing elements failed");
}

void test_top(void) {
    printf("%s", __func__);

    if (top(test_file) != e1)
        FAIL("Getting top element failed");
}

void test_pop(void) {
    printf("%s", __func__);

    pop(test_file);

    if (number_of_element_file(test_file) != 2 || top(test_file) != e2)
        FAIL("Popping element failed");
}

int test_file_main(void) {
    TEST(test_init);
    TEST(test_push);
    TEST(test_top);
    TEST(test_pop);

    SUMMARY();

    return EXIT_SUCCESS;
}
