SHELL := /bin/bash

# Making sure no parallelization is performed
.NOTPARALLEL:

# Compiler choice.
# Default: gcc
ifndef $CC
CC:=gcc
endif

# Sub-directory of (unpeeled) source code
# Default: source/original
ifndef $ORIGINAL
ORIGINAL:=source/original
endif

# Sub-directory of peeled source code
# Default: peeled
ifndef $PEELED
PEELED:=source/peeled
endif

# Optimization levels
OPT_LEVEL = O0
# Can be one among
# O0 O1 O2 O3

# This command need to run first
# make set-up
# to create the required directory structure
.PHONY:set-up
set-up:
	mkdir -p bin/peeled bin/original

bin/%.out:source/%.c
	gcc $< -$(OPT_LEVEL) -o $@
# Can be used as
# make bin/original/Fact4.out
# To compile bin/original/Fact4.out using source/original/Fact4.c

clean:
	rm -rf bin/
# Command to clean what we have so far.

all: set-up bin/original/Fact4.out 
# This means 
# > "make all" is interpretend as "make set-up" followed by "make bin/original/Fact4.out".
