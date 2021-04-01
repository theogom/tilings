#include "../src/opt.h"
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>

#define MAIN "./project"

//TESTED FUNCTIONS/////////////////////////////////////////
/*
int parse_opts(int argc, char *argv[]);
*/
///////////////////////////////////////////////////////////

extern int seed;
extern int nb_player;
extern int board_size;

int parse_opts_reset(int argc, char *argv[])
{
    // Reset optind to use getopt() multiple times
    optind = 1;
    return parse_opts(argc, argv);
}

void opt_test()
{
    int argc;
    // Test options
    char b_valid[10];
    char n_valid[10];
    char b_invalid[10];
    char n_invalid[10];
    char *s_option = "528491";

    sprintf(b_valid, "%d", MIN_BOARD_SIZE + 1);
    sprintf(n_valid, "%d", MIN_NB_PLAYER + 1);
    sprintf(b_invalid, "%d", MAX_BOARD_SIZE + 1);
    sprintf(n_invalid, "%d", MIN_NB_PLAYER - 1);

    // Regular case (check if options are initialized correctly)
    printf("TEST: Handling of valid options...");
    argc = 7;
    char *argv_valid[] = {MAIN, "-b", b_valid, "-n", n_valid, "-s", s_option};
    if (parse_opts(argc, argv_valid) || board_size != atoi(b_valid) || nb_player != atoi(n_valid) || seed != atoi(s_option))
    {
        printf("\e[31mFAILED\n");
        printf("ERROR: Bad handling of valid options\e[m\n");
        exit(EXIT_FAILURE);
    }
    printf("\e[32mSUCCEED\e[m\n");

    // Invalid case
    printf("TEST: Handling of invalid options...");
    argc = 3;
    char *argv_invalid_b[] = {MAIN, "-b", b_invalid};
    char *argv_invalid_n[] = {MAIN, "-n", n_invalid};
    if (!(parse_opts_reset(argc, argv_invalid_b) && parse_opts_reset(argc, argv_invalid_n)))
    {
        printf("\e[31mFAILED\n");
        printf("ERROR: Bad handling of invalid options\e[m\n");
        exit(EXIT_FAILURE);
    }
    printf("\e[32mSUCCEED\e[m\n");

    // Illegal case
    printf("TEST: Handling of illegal options...");
    char *argv_illegal[] = {MAIN, "-x", "13"};
    if (!parse_opts_reset(argc, argv_illegal))
    {
        printf("\e[31mFAILED\n");
        printf("ERROR: Bad handling of illegal options\e[m\n");
        exit(EXIT_FAILURE);
    }
    printf("\e[32mSUCCEED\e[m\n");
}

int main(void)
{
    printf("\nPerforming options tests...\n");
    // Close stderr to not print parse_opts() errors
    fclose(stderr);
    opt_test();
    return EXIT_SUCCESS;
}
