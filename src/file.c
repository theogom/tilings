#include "file.h"
#include <stdio.h>
#include <stdlib.h>

// Element of a file
struct element {
    struct element* next_element;
    const void* data; // It can be a player or a tile in our program
};

// A control structure for a file
struct file {
    struct element* first_element;
};

// Initialize an empty file
struct file* file_init(void) {
    struct file* f = malloc(sizeof(struct file));
    set_top(f, NULL);
    return f;
}

// Create a new element
struct element* create_element(void) {
    struct element* e = malloc(sizeof(struct element));
    set_next_element(e, NULL);
    set_data(e, NULL);
    return e;
}

// Get the total amount of element in a file
int number_of_element_file(struct file* f) {
    int count_element = 0;
    struct element* actual_element = top(f);
    while (actual_element != NULL) {
        count_element++;
        actual_element = get_next_element(actual_element);
    }
    return count_element;
}

// Add a element at the end of the file
void push(struct file* f, struct element* element_to_push) {
    // Reset the next element pointer to NULL
    set_next_element(element_to_push, NULL);
    // If the file is empty then we add the element at the first place
    if (top(f) == NULL) {
        set_top(f, element_to_push);
    }
    else {
        struct element* actual_element = top(f);
        // We go through the file until we find the last element
        while (get_next_element(actual_element) != NULL) {
            actual_element = get_next_element(actual_element);
        }
        set_next_element(actual_element, element_to_push);
    }
}

// Remove the top element from a file
void pop(struct file* f) {
    // Check if the file is not empty
    if (top(f) != NULL) {
        struct element* element_to_pop = top(f);
        set_top(f, get_next_element(element_to_pop));
    }
    else {
        fprintf(stderr, "ERROR: Trying to pop an element on an empty file\n");
        exit(EXIT_FAILURE);
    }
}

// GETTER FUNCTIONS //
// Get the element at the top of a file
struct element* top(struct file* f) {
    return f->first_element;
}

// Get the next element in the linked list
struct element* get_next_element(struct element* e) {
    return e->next_element;
}

//SETTER FUNCTIONS//
// Get the data stored in an element
const void* get_element_data(struct element* e) {
    return e->data;
}

// Set the first element of a file
void set_top(struct file* f, struct element* e) {
    f->first_element = e;
}

// Set the next element in the linked list
void set_next_element(struct element* e1, struct element* e2) {
    e1->next_element = e2;
}

// Set the data in an element
void set_data(struct element* e, const void* data) {
    e->data = data;
}
