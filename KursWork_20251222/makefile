# Определение операционной системы
UNAME_S := $(shell uname -s 2>/dev/null)
ifeq ($(OS),Windows_NT)
    DETECTED_OS := Windows
else ifeq ($(UNAME_S),Darwin)
    DETECTED_OS := macOS
else ifeq ($(UNAME_S),Linux)
    DETECTED_OS := Linux
else
    $(error Не удалось определить ОС. OS=$(OS), UNAME_S=$(UNAME_S))
endif

# Настройки
CC := gcc
CFLAGS := -Wall -Wextra -std=c11 -O2

# Имя исполняемого файла в зависимости от ОС
ifeq ($(DETECTED_OS),Windows)
    TARGET := temp_info.exe
    RM := del /Q
    RUN_CMD := .\\temp_info.exe
else
    TARGET := temp_info
    RM := rm -f
    RUN_CMD := ./temp_info
endif

# Объектные файлы
OBJS := main.o temp_functions.o

# Цель по умолчанию
all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

main.o: main.c temp_functions.h
	$(CC) $(CFLAGS) -c -o $@ $<

temp_functions.o: temp_functions.c temp_functions.h
	$(CC) $(CFLAGS) -c -o $@ $<

# Очистка: удаляем объектные файлы и исполняемый
clean:
	$(RM) $(OBJS) $(TARGET)


run: $(TARGET)
	$(RUN_CMD) -h