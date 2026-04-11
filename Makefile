CC = gcc
CFLAGS = -Wall -g

SRCS = $(wildcard *.c)
TARGETS = $(SRCS:.c=)

%: %.c
	$(CC) $(CFLAGS) -o $@ $<

$(TARGETS):

all: $(TARGETS)

clean:
	rm -f $(TARGETS)
.PHONY: all clean
help:
	@echo "Available Targets:"
	@echo "$(TARGETS)"