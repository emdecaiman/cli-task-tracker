CC = gcc
CFLAGS = -Wall -Wextra -g -Iinclude -l sqlite3

SRCS = $(wildcard src/*.c)
EXEC = task-cli

all: $(EXEC)

$(EXEC): $(SRCS)
	$(CC) $(CFLAGS) -o $@ $^

clear:
	rm -f $(EXEC)
