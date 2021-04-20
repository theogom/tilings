#include "tests.h"
#include "tile.h"
#include <stdlib.h>

extern struct tile tile1;
extern struct tile tile2;

static void setup(void) {
    return;
}

static void teardown(void) {
    return;
}

// Check if empty tile is empty
void test_empty(void) {
    printf("%s", __func__);

    if (!tile_is_empty(empty_tile()))
        FAIL("Empty tile is not empty");
}

// Check if non-empty tile is non-empty
void test_non_empty(void) {
    printf("%s", __func__);

    if (tile_is_empty(&tile1))
        FAIL("Non-empty tile is empty");
}

// Check if equal tiles are equals
void test_equals(void) {
    printf("%s", __func__);

    if (!tile_equals(&tile1, &tile1))
        FAIL("Equals tiles are non-equals");
}

void test_non_equals(void) {
    printf("%s", __func__);

    if (tile_equals(&tile1, &tile2))
        FAIL("Non-equals tiles are equals");
}

// Check if we correctly get the color of the edges
void test_get_edge_color(void) {
    printf("%s", __func__);

    if (tile_edge(&tile1, SOUTH) != color_from_name("BLUE") ||
        tile_edge(&tile1, WEST) != color_from_name("RED"))
        FAIL("Unable to get edge color");
}

int test_tile_main(void) {
    TEST(test_empty);
    TEST(test_non_empty);
    TEST(test_equals);
    TEST(test_non_equals);
    TEST(test_get_edge_color);

    SUMMARY();

    return EXIT_SUCCESS;
}
