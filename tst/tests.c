#include "tests.h"
#include <stdlib.h>
#include <stdio.h>

int main(void) {
    RUN(test_color_main);
    RUN(test_tile_main);
    RUN(test_file_main);
    RUN(test_player_main);
    RUN(test_board_main);
    RUN(test_opt_main);

    MAIN_SUMMARY();

    return EXIT_SUCCESS;
}