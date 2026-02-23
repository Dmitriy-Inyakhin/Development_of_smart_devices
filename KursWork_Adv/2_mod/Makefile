# Makefile для сборки программы area_calc

CC = gcc
# Флаги компиляции (без -lm)
CFLAGS = -std=c99 -Wall -Wextra
# Флаги линковки (с -lm)
LDFLAGS = -lm

TARGET = area_calc
SRCS = main.c math_lib.c
OBJS = $(SRCS:.c=.o)

all: $(TARGET)

# На этапе линковки добавляем LDFLAGS
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS) $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

main.o: main.c math_lib.h
math_lib.o: math_lib.c math_lib.h

clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: all clean