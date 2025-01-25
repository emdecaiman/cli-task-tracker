CC = gcc
CFLAGS = -Wall -Wextra -g -Iinclude -l sqlite3

SRCS = src/main.c src/controller.c src/model.c src/view.c
EXEC = task-cli

all: $(EXEC)

$(EXEC): $(SRCS)
	$(CC) $(CFLAGS) -o $@ $^

clear:
	rm -f $(EXEC)
