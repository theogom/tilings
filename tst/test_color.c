#include "../src/color.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//TESTED FUNCTIONS/////////////////////////////////////////
/*
const char* color_name(struct color* t);

const char* color_cstring(struct color* t);

struct color* color_from_name(const char* name);
*/
///////////////////////////////////////////////////////////

extern struct color red;

void color_test()
{
    // Check if we get the correct color name
    printf("TEST: Getting color name...");
    if (strcmp(color_name(&red), "RED"))
    {
        printf("\e[31mFAILED\n");
        fprintf(stderr, "ERROR: Unable to get color name\e[m\n");
        exit(EXIT_FAILURE);
    }
    printf("\e[32mSUCCEED\e[m\n");

    // Check if we get the correct ANSI color code
    printf("TEST: Getting ANSI color code...");
    if (strcmp(color_cstring(&red), "\e[41m"))
    {
        printf("\e[31mFAILED\n");
        fprintf(stderr, "ERROR: Unable to get ANSI color code\e[m\n");
        exit(EXIT_FAILURE);
    }
    printf("\e[32mSUCCEED\e[m\n");

    // Check if we can correctly get a color from its name
    printf("TEST: Getting a color from its name...");
    if (color_from_name("RED") != &red)
    {
        printf("\e[31mFAILED\n");
        fprintf(stderr, "ERROR: Unable to get a color from its name\e[m\n");
        exit(EXIT_FAILURE);
    }
    printf("\e[32mSUCCEED\e[m\n");
}

int main(void)
{
    printf("\nPerforming color tests...\n");
    color_test();
    return EXIT_SUCCESS;
}