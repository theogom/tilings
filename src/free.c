#include "free.h"
#include <stdio.h>
#include <stdlib.h>

extern struct file* players;

// Counter for memory debugging and testing
int free_f = 0;
int free_e = 0;
int free_p = 0;

// Free a file and its elements
void free_file(struct file* file_to_free) {
    free_f++;
    struct element* actual_element = top(file_to_free);
    struct element* next_element = NULL;
    // First, free all the elements of the file
    while (actual_element != NULL) {
        next_element = get_next_element(actual_element);
        free(actual_element);
        free_e++;
        actual_element = next_element;
    }
    // Finally, free the file itself
    free(file_to_free);
}

// Free all the allocated space
void free_all(void) {
    struct element* actual_element = top(players);
    const struct player* actual_player;
    // First free all player's stack
    while (actual_element != NULL) {
        actual_player = player_from_element(actual_element);
        free_file(get_stack(actual_player));
        free((void*)actual_player);
        free_p++;
        actual_element = get_next_element(actual_element);
    }
    // Free the players file
    free_file(players);
    // Memory debug message
    // memory_debug();
}

// Print a message for memory debugging
void memory_debug(void) {
    printf("### DEBUG INFO :\n");
    printf("%d files (players file and %d stacks), %d elements and %d players were freed\n",
        free_f, free_f - 1, free_e, free_p);
}