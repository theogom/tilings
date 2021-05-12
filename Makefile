# Directories
SRCDIR = src
CMPDIR = build
EXECDIR = bin
DEPDIR = deps
TSTDIR = tst

# Variables for colored output
RESET=\033[m
RED=\033[31m
GREEN=\033[32m
YELLOW=\033[33m

# Get all source files excepted main.c (Excluded to avoid duplicate symbol main when compiling tests)
MAIN = tilings
MAINTST = alltests
SRC = $(filter-out $(SRCDIR)/main.c, $(wildcard $(SRCDIR)/*.c))
SRCTST = $(wildcard $(TSTDIR)/*.c)

# Naming of object and dependency files according to source files
OBJ = $(SRC:$(SRCDIR)/%.c=$(CMPDIR)/%.o)
OBJTST = $(SRCTST:$(TSTDIR)/%.c=$(CMPDIR)/%.o)
DEPFILES = $(OBJ:$(CMPDIR)/%.o=$(DEPDIR)/%.d) $(OBJTST:$(CMPDIR)/%.o=$(DEPDIR)/%.d) $(DEPDIR)/main.d

# Get the number of tests available in the TSTDIR directory
NBTST= $$(($(shell ls $(TSTDIR) | wc -l)))

# Compilation flags
CC = gcc
CFLAGS = -Wall -Wextra -std=gnu99 -I src
DEPFLAGS = -MT $@ -MMD -MP -MF $(DEPDIR)/$*.d


all: $(CMPDIR)/$(MAIN)

# SCRIPTS

game: $(EXECDIR)/$(MAIN)
	$(EXECDIR)/$(MAIN)

.PHONY: test
test: $(EXECDIR)/$(MAINTST)
	$(EXECDIR)/$(MAINTST)

.PHONY: install
install: $(CMPDIR)/$(MAIN) $(CMPDIR)/$(MAINTST) | $(EXECDIR)
	@for file in $^; do cp $$file $(EXECDIR); done
	@printf "$(GREEN)Project installed in $(EXECDIR)$(RESET)\n"

# Make project with all object files
$(CMPDIR)/$(MAIN): $(OBJ) $(CMPDIR)/main.o
	@printf "$(GREEN)Build success$(RESET)\n"
	@echo "Linking objects..."
	@$(CC) $(CFLAGS) $^ -o $@
	@printf "$(GREEN)Successfully making project$(RESET)\n"

$(CMPDIR)/$(MAINTST): $(OBJ) $(OBJTST) | $(CMPDIR)
	@$(CC) $^ -o $@

# Build object files
$(CMPDIR)/%.o: $(SRCDIR)/%.c $(DEPDIR)/%.d | $(CMPDIR) $(DEPDIR)
	@printf "Building $(YELLOW)$(@:$(CMPDIR)/%.o=%.o)$(RESET)...\n"
	@$(CC) $(CFLAGS) $(DEPFLAGS) -c $< -o $@

# Build test object files
$(CMPDIR)/%.o: $(TSTDIR)/%.c $(DEPDIR)/%.d | $(CMPDIR) $(DEPDIR)
	@printf "Building $(YELLOW)$(@:$(CMPDIR)/%.o=%.o)$(RESET)...\n"
	@$(CC) $(CFLAGS) $(DEPFLAGS) -c $< -o $@

# Create directory for object files
$(CMPDIR):
	@echo "Creating build directory..."
	@mkdir -p $@

$(EXECDIR):
	@echo "Creating install directory..."
	@mkdir -p $@

# Create directory for dependencies
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
