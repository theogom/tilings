#include "tests.h"
#include "opt.h"
#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>

#define MAIN "./project"

extern int seed;
extern int nb_player;
extern int board_size;

static void setup(void) {
    return;
}

// Reset optind to use getopt() multiple times
static void teardown(void) {
    optind = 1;
}

// Close stderr to not print parse_opts() errors
int parse_opts_without_stderr(int argc, char** argv) {
    int res;
    int stderr_copy = dup(STDERR_FILENO);
    fclose(stderr);

    res = parse_opts(argc, argv);

    dup2(stderr_copy, STDERR_FILENO);

    return res;
}

int argc;
// Test options
char b_valid[10];
char n_valid[10];
char b_invalid[10];
char n_invalid[10];
char *s_option = "528491";

// Regular case (check if options are initialized correctly)
void test_valid(void) {
    printf("%s", __func__);

    argc = 7;
    char *argv_valid[] = {MAIN, "-b", b_valid, "-n", n_valid, "-s", s_option};

    if (parse_opts_without_stderr(argc, argv_valid) != EXIT_SUCCESS)
        FAIL("Unable to parse valid options");

    if (board_size != atoi(b_valid))
        FAIL("Board size not initialized");

    if (nb_player != atoi(n_valid))
        FAIL("Number of players not initialized");

    if (seed != atoi(s_option))
        FAIL("Seed not initialized");
}

// Invalid case
void test_invalid_board(void) {
    printf("%s", __func__);

    argc = 3;
    char *argv_invalid_b[] = {MAIN, "-b", b_invalid};

    if (parse_opts_without_stderr(argc, argv_invalid_b) == EXIT_FAILURE)
        FAIL("Bad handling of invalid board size");
}

void test_invalid_players(void) {
    printf("%s", __func__);

    argc = 3;
    char *argv_invalid_n[] = {MAIN, "-n", n_invalid};

    if (parse_opts_without_stderr(argc, argv_invalid_n) != EXIT_FAILURE)
        FAIL("Bad handling of invalid number of players");
}

// Illegal case
void test_illegal(void) {
    printf("%s", __func__);

    char *argv_illegal[] = {MAIN, "-x", "13"};

    if (parse_opts_without_stderr(argc, argv_illegal) != EXIT_FAILURE)
        FAIL("Bad handling of illegal options");
}

int test_opt_main(void) {

    sprintf(b_valid, "%d", MIN_BOARD_SIZE + 1);
    sprintf(n_valid, "%d", MIN_NB_PLAYER + 1);
    sprintf(b_invalid, "%d", MAX_BOARD_SIZE + 1);
    sprintf(n_invalid, "%d", MIN_NB_PLAYER - 1);

    TEST(test_valid);
    TEST(test_invalid_board);
    TEST(test_invalid_players);
    TEST(test_illegal);

    SUMMARY();

    return END;
}
