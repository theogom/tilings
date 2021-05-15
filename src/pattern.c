#include "pattern.h"
#include <stdio.h>
#include <string.h>

int (*patterns[]) (int, int) = { &pattern_1, &pattern_2, &pattern_3 };
void (*print_patterns[]) () = { &print_pattern_1, &print_pattern_2, &print_pattern_3 };

int score_pattern_1 = 30;
int score_pattern_2 = 15;
int score_pattern_3 = 100;

//  ____________________
// |      |      |      |
// |      |      |      |
// |______|__R___|______|
// |      |  R   |      |
// |     R|R    R|R     |
// |______|______|______|
// |      |      |      |
// |      |      |      |
// |______|______|______|
int pattern_1(int i, int j) {
    int valid = 0;
    valid = ((i > 0) && (j > 0) && (j < board_size - 1)) ? 1 : 0;
    if (valid) {
        // tile i, j
        valid = (valid && check_color_dir(i, j, EAST, "RED")) ? 1 : 0;
        valid = (valid && check_color_dir(i, j, WEST, "RED")) ? 1 : 0;
        valid = (valid && check_color_dir(i, j, NORTH, "RED")) ? 1 : 0;

        // tile i, j+1
        valid = (valid && check_color_dir(i, j + 1, WEST, "RED")) ? 1 : 0;

        // tile i, j-1
        valid = (valid && check_color_dir(i, j - 1, EAST, "RED")) ? 1 : 0;

        // tile i-1, j
        valid = (valid && check_color_dir(i - 1, j, SOUTH, "RED")) ? 1 : 0;
    }
    return valid ? score_pattern_1 : 0;
}

//  ____________________
// |      |      |      |
// |      |      |      |
// |______|______|______|
// |      |      |      |
// |     R|R    R|R     |
// |______|______|______|
// |      |      |      |
// |      |      |      |
// |______|______|______|
int pattern_2(int i, int j) {
    int valid = 0;
    valid = ((j > 0) && (j < board_size - 1)) ? 1 : 0;
    if (valid) {
        // tile i, j
        valid = (valid && check_color_dir(i, j, EAST, "RED")) ? 1 : 0;
        valid = (valid && check_color_dir(i, j, WEST, "RED")) ? 1 : 0;

        // tile i, j+1
        valid = (valid && check_color_dir(i, j + 1, WEST, "RED")) ? 1 : 0;

        // tile i, j-1
        valid = (valid && check_color_dir(i, j - 1, EAST, "RED")) ? 1 : 0;
    }
    return valid ? score_pattern_2 : 0;
}

//  ____________________
// |      |      |      |
// |      |      |      |
// |___R__|______|___R__|
// |   R  |      |   R  |
// |     R|R    R|R     |
// |______|______|______|
// |      |      |      |
// |      |      |      |
// |______|______|______|
int pattern_3(int i, int j) {
    int valid = 0;
    valid = ((i > 0) && (j > 0) && (j < board_size - 1)) ? 1 : 0;
    if (valid) {
        // tile i, j
        valid = (valid && check_color_dir(i, j, EAST, "RED")) ? 1 : 0;
        valid = (valid && check_color_dir(i, j, WEST, "RED")) ? 1 : 0;

        // tile i, j+1
        valid = (valid && check_color_dir(i, j + 1, WEST, "RED")) ? 1 : 0;
        valid = (valid && check_color_dir(i, j + 1, NORTH, "RED")) ? 1 : 0;

        // tile i, j-1
        valid = (valid && check_color_dir(i, j - 1, EAST, "RED")) ? 1 : 0;
        valid = (valid && check_color_dir(i, j - 1, NORTH, "RED")) ? 1 : 0;

        // tile i-1, j+1
        valid = (valid && check_color_dir(i - 1, j + 1, SOUTH, "RED")) ? 1 : 0;

        // tile i-1, j-1
        valid = (valid && check_color_dir(i - 1, j - 1, SOUTH, "RED")) ? 1 : 0;
    }
    return valid ? score_pattern_3 : 0;
}

void print_pattern_1(void) {
    const char* empty = "\e[0m";
    const char* red = "\e[41m";
    printf("\n");
    printf(" ____________________ \n");
    printf("|      |      |      |\n");
    printf("|      |      |      |\n");
    printf("|______|__%s__%s__|______|\n", red, empty);
    printf("|      |  %s  %s  |      |\n", red, empty);
    printf("|    %s  %s|%s  %s  %s  %s|%s  %s    |\n", red, empty, red, empty, red, empty, red, empty);
    printf("|______|______|______|\n");
    printf("|      |      |      |\n");
    printf("|      |      |      |\n");
    printf("|______|______|______|\n");
    printf("Score: %d\n", score_pattern_1);
}
void print_pattern_2(void) {
    const char* empty = "\e[0m";
    const char* red = "\e[41m";
    printf("\n");
    printf(" ____________________ \n");
    printf("|      |      |      |\n");
    printf("|      |      |      |\n");
    printf("|______|______|______|\n");
    printf("|      |      |      |\n");
    printf("|    %s  %s|%s  %s  %s  %s|%s  %s    |\n", red, empty, red, empty, red, empty, red, empty);
    printf("|______|______|______|\n");
    printf("|      |      |      |\n");
    printf("|      |      |      |\n");
    printf("|______|______|______|\n");
    printf("Score: %d\n", score_pattern_2);
}
void print_pattern_3(void) {
    const char* empty = "\e[0m";
    const char* red = "\e[41m";
    printf("\n");
    printf(" ____________________ \n");
    printf("|      |      |      |\n");
    printf("|      |      |      |\n");
    printf("|__%s__%s__|______|__%s__%s__|\n", red, empty, red, empty);
    printf("|  %s  %s  |      |  %s  %s  |\n", red, empty, red, empty);
    printf("|    %s  %s|%s  %s  %s  %s|%s  %s    |\n", red, empty, red, empty, red, empty, red, empty);
    printf("|______|______|______|\n");
    printf("|      |      |      |\n");
    printf("|      |      |      |\n");
    printf("|______|______|______|\n");
    printf("Score: %d\n", score_pattern_3);
}


void print_all_patterns(void) {
    for (int p = 0; p < NB_PATTERN; ++p) {
        print_patterns[p]();
    }
}
