CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -O2

TARGET = temp_stats
SOURCES = main.c cli.c temp_functions.c
OBJECTS = $(SOURCES:.c=.o)

$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJECTS) $(TARGET)

.PHONY: clean