# Компилятор и флаги
CC := gcc
CFLAGS := -Wall -Wextra -std=c99 -O2

# Имя исполняемого файла (единое, с .exe на Windows)
UNAME_S := $(shell uname -s 2>/dev/null)
ifeq ($(OS),Windows_NT)
    TARGET := sensor_app.exe
    RUN_CMD := ./sensor_app.exe
else ifeq ($(UNAME_S),Darwin)
    TARGET := sensor_app
    RUN_CMD := ./sensor_app
else
    TARGET := sensor_app
    RUN_CMD := ./sensor_app
endif

# Объектные файлы
OBJS := main.o temp_functions.o

# Сборка
all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

main.o: main.c temp_functions.h
	$(CC) $(CFLAGS) -c -o $@ $<

temp_functions.o: temp_functions.c temp_functions.h
	$(CC) $(CFLAGS) -c -o $@ $<

# Очистка — единая для всех ОС
clean:
	-rm -f $(OBJS) $(TARGET)

# Запуск
.PHONY: all clean run

run: $(TARGET)
	$(RUN_CMD) -h