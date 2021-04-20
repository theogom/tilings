#ifndef TILINGS_TESTS_H
#define TILINGS_TESTS_H

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

// Test macros
static int pass;
static int passed = 0;
static int total = 0;
// Run a test
#define TEST(f) pass = true, setup(), f(), teardown(), printf("\t%s\n", pass ? "OK" : "FAIL"), passed += pass, total++
// Print error message
#define FAIL(msg) fprintf(stderr, "ERROR: %s\n", msg), pass = false
// Print the summary for a test suit
#define SUMMARY() printf("%s(%d/%d) --> %s\n\n", __func__, passed, total, passed == total ? "PASSED" : "FAILED")
// Run a test suite
#define RUN(f) pass = f() == EXIT_SUCCESS ? true : false, passed += pass, total++
#define MAIN_SUMMARY() printf("%d test suites ran, %d/%d succeed\n", total, passed, total)
#define END passed == total ? EXIT_SUCCESS : EXIT_FAILURE

int test_color_main(void);
int test_tile_main(void);
int test_file_main(void);
int test_player_main(void);
int test_board_main(void);
int test_opt_main(void);
int test_free_main(void);

#endif //TILINGS_TESTS_H
