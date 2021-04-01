#include "file.h"
#include "player.h"

// Free a file and its elements
void free_file(struct file *file_to_free);

// Free all the allocated space
// TO FREE :
// -stack tile elements
// -stack file
// -tile elements placed on the board (freed directly when placed)
// -players
// -players list elements
// -players file
void free_all(void);

// Print a message for memory debugging
void memory_debug(void);