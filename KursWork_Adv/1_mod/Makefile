# Компилятор и флаги
CC = gcc
CFLAGS = -std=c99 -Wall -Wextra -pedantic -g
LDFLAGS = -lm

# Имена файлов
TARGET = area_calc
SRCS = main.c math_solver.c tests.c
OBJS = $(SRCS:.c=.o)

# Цели
.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Зависимости заголовков
main.o: main.c math_solver.h
math_solver.o: math_solver.c math_solver.h
tests.o: tests.c math_solver.h

clean:
	rm -f $(OBJS) $(TARGET)