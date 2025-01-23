CC = gcc
CFLAGS = -WALL -Wextra -g -Iinclude

SRCS = src/main.c src/controller.c src/model.c src/view.c
EXEC = task-cli

all: $(EXEC)

$(EXEC): $(SRCS)
	$(CC) $(CFLAGS) -o $@ $^

clear:
	rm -f $(EXEC)