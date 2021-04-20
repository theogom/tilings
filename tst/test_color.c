#include "tests.h"
#include "color.h"
#include <stdlib.h>
#include <string.h>

extern struct color red;

static void setup(void) {
    return;
}

static void teardown(void) {
    return;
}

// Check if we get the correct color name
void test_color_name(void) {
    printf("%s", __func__);

    if (strcmp(color_name(&red), "RED") != 0)
        FAIL("Unable to get color name");
}

// Check if we get the correct ANSI color code
void test_color_code(void) {
    printf("%s", __func__);

    if (strcmp(color_cstring(&red), "\e[41m") != 0)
        FAIL("Unable to get ANSI color code");
}

// Check if we can correctly get a color from its name
void test_color_from_name(void) {
    printf("%s", __func__);

    if (color_from_name("RED") != &red)
        FAIL("Unable to get a color from its name");
}

int test_color_main(void) {
    TEST(test_color_name);
    TEST(test_color_code);
    TEST(test_color_from_name);

    SUMMARY();

    return EXIT_SUCCESS;
}