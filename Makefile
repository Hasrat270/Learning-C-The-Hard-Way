CC = gcc
CFLAGS = -Wall -g -I. -I./05-Debugging_and_Macros -I./13-Safer_Strings -I./11-Lists_and_Algos -I./12-Dynamic_Arrays -I./14-Hashmaps -I./16-Trees -I./19-Ring_Buffer -I./20-Stats_Engine
LDFLAGS = -lm

# Saare sub-directories
SUBDIRS = $(wildcard */)

# Saare .c files
SRCS = $(wildcard $(addsuffix *.c,$(SUBDIRS)))

# Programs (Exclude Files ending with _Library)
BINS = $(filter-out %_Library, $(SRCS:.c=))

# Rule to compile programs and link with their local Library if exists
%: %.c
	@echo "Compiling $@..."
	$(CC) $(CFLAGS) -o $@ $< $(wildcard $(dir $@)*_Library.c) $(LDFLAGS)

all: $(BINS)

clean:
	@echo "Cleaning up..."
	find . -type f -executable -not -path '*/.*' -not -name "*.sh" -delete

.PHONY: all clean help

help:
	@echo "Available Exercises (Standalone & Tests):"
	@echo "$(sort $(BINS))" | tr ' ' '\n'