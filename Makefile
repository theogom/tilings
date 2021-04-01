# Directories
SRCDIR = src
OBJDIR = build
DEPDIR = deps
TSTDIR = tst

# Variables for colored output
RESET=\033[m
RED=\033[31m
GREEN=\033[32m
YELLOW=\033[33m

# Get all source files excepted project.c (Excluded to avoid duplicate symbol _main when compiling tests)
MAIN = project
SRC = $(filter-out $(SRCDIR)/$(MAIN).c, $(wildcard $(SRCDIR)/*.c))
SRCTST = $(wildcard $(TSTDIR)/*.c)

# Naming of object and dependency files according to source files
OBJ = $(SRC:$(SRCDIR)/%.c=$(OBJDIR)/%.o)
OBJTST = $(SRCTST:$(TSTDIR)/%.c=$(OBJDIR)/%.o)
DEPFILES = $(OBJ:$(OBJDIR)/%.o=$(DEPDIR)/%.d) $(OBJTST:$(OBJDIR)/%.o=$(DEPDIR)/%.d) $(DEPDIR)/$(MAIN).d

# Get the number of tests available in the TESTDIR directory
NBTST= $$(($(shell ls $(TSTDIR) | wc -l)))

# Compilation flags
CC = gcc
CFLAGS = -Wall -Wextra -std=gnu99
DEPFLAGS = -MT $@ -MMD -MP -MF $(DEPDIR)/$*.d


all: $(MAIN)

# Make project with all object files
$(MAIN): $(OBJ) $(OBJDIR)/$(MAIN).o
	@printf "$(GREEN)Build success$(RESET)\n"
	@echo "Linking objects..."
	@$(CC) $(CFLAGS) $^ -o $@
	@printf "$(GREEN)Successfully making project$(RESET)\n"

# Make tests
# Phony target in order to run the tests even if there is already an file named test in the directory
.PHONY: test
test: $(OBJ) $(OBJTST)
	@for tst in $(OBJTST); do \
	$(CC) $(CFLAGS) $(OBJ) $$tst -o test && ./test && SUCCESS=$$(($$SUCCESS + 1)); done; \
	printf "\nSUMMARY: $(NBTST) tests ran, $$SUCCESS $(GREEN)passed$(RESET), $$(($(NBTST) - $$SUCCESS)) $(RED)failed$(RESET)\n"

# Build object files
$(OBJDIR)/%.o: $(SRCDIR)/%.c $(DEPDIR)/%.d | $(OBJDIR) $(DEPDIR)
	@printf "Building $(YELLOW)$(@:$(OBJDIR)/%.o=%.o)$(RESET)...\n"
	@$(CC) $(CFLAGS) $(DEPFLAGS) -c $< -o $@

# Build test object files
$(OBJDIR)/%.o: $(TSTDIR)/%.c $(DEPDIR)/%.d | $(OBJDIR) $(DEPDIR)
	@printf "Building $(YELLOW)$(@:$(OBJDIR)/%.o=%.o)$(RESET)...\n"
	@$(CC) $(CFLAGS) $(DEPFLAGS) -c $< -o $@

# Create directory for object files
$(OBJDIR):
	@echo "Creating build directory..."
	@mkdir -p $@

# Create directory for dependancies
$(DEPDIR):
	@echo "Creating dependency directory..."
	@mkdir -p $@

# Include dependencies
$(DEPFILES):
include $(wildcard $(DEPFILES))

# Clean the place
TRASH = build deps project test
clean:
	@echo "Cleaning the place..."
	@for JUNK in $(TRASH); do \
	if [ -e $$JUNK ]; then \
	rm -rf $$JUNK && printf "$(RED)$$JUNK removed$(RESET)\n" ; fi; done
	@printf "$(GREEN)All clear !$(RESET)\n"