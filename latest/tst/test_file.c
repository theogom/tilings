#include "../src/file.h"
#include "../src/free.h"
#include <stdio.h>
#include <stdlib.h>

//TESTED FUNCTIONS/////////////////////////////////////////
/*
void push(struct file* f, struct tile* t);

struct tile* top(struct file* f);

void pop(struct file* f);

struct file* file_init();
*/
///////////////////////////////////////////////////////////

//Perform all the file test
void file_test()
{
	//Test the file initialization
	printf("TEST: File initialization\n");
	struct file *test_file = file_init();
	if (number_of_element_file(test_file) != 0)
	{
		free_file(test_file);
		printf("\e[31mFAILED\n");
		fprintf(stderr, "ERROR: File initialization failed\n");
		exit(EXIT_FAILURE);
	}

	//Test pushing elements into the file
	printf("TEST: Pushing 3 tiles into the file...");
	struct element *e1 = create_element();
	struct element *e2 = create_element();
	struct element *e3 = create_element();
	push(test_file, e1);
	push(test_file, e2);
	push(test_file, e3);
	if (number_of_element_file(test_file) != 3)
	{
		free_file(test_file);
		printf("\e[31mFAILED\n");
		fprintf(stderr, "ERROR: Pushing elements failed\e[m\n");
		exit(EXIT_FAILURE);
	}
	printf("\e[32mSUCCEED\e[m\n");

	//Test getting the top element
	printf("TEST: Getting the top element...");
	if (top(test_file) != e1)
	{
		free_file(test_file);
		printf("\e[31mFAILED\n");
		fprintf(stderr, "ERROR: Unable to get top element\e[m\n");
		exit(EXIT_FAILURE);
	}
	printf("\e[32mSUCCEED\e[m\n");

	//Test popping the top tile
	printf("TEST: Popping the top tile...");
	pop(test_file);
	if (number_of_element_file(test_file) != 2 || top(test_file) != e2)
	{
		free_file(test_file);
		printf("\e[31mFAILED\n");
		fprintf(stderr, "ERROR: Popping element failed\e[m\n");
		exit(EXIT_FAILURE);
	}
	free_file(test_file);
	printf("\e[32mSUCCEED\e[m\n");
}

int main(void)
{
	printf("\nPerforming file tests...\n");
	file_test();
	return EXIT_SUCCESS;
}