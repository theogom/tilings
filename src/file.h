#ifndef __FILE_H_
#define __FILE_H_

// Element of a file
struct element;

// A control structure for a file
struct file;

// Initialize an empty file
struct file *file_init(void);

// Create a new element
struct element *create_element(void);

// Get the total amount of element in a file
int number_of_element_file(struct file *f);

// Add a element at the end of the file
void push(struct file *f, struct element *e);

// Remove an element from the file
void pop(struct file *f);

// Get the element at the top of the file
struct element *top(struct file *f);

// Get the next element in the linked list
struct element *get_next_element(struct element *e);

// Get the data stored in an element
const void *get_element_data(struct element *e);

// Set the first element of a file
void set_top(struct file *f, struct element *e);

// Set the next element in the linked list
void set_next_element(struct element *e1, struct element *e2);

// Set the data in an element
void set_data(struct element *e, const void *data);

#endif // __FILE_H_
