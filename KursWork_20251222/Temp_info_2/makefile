# Компилятор и флаги
# -Os → оптимизация по размеру (вместо -O2)
# -s → убрать отладочные символы при линковке
CC := gcc
CFLAGS := -Wall -Wextra -std=c99 -Os -s -fno-unwind-tables

# Имя исполняемого файла (единое, с .exe на Windows)
UNAME_S := $(shell uname -s 2>/dev/null)
ifeq ($(OS),Windows_NT)
TARGET := temp_info.exe
RUN_CMD := ./temp_info.exe
else ifeq ($(UNAME_S),Darwin)
TARGET := temp_info
RUN_CMD := ./temp_info
else
TARGET := temp_info
RUN_CMD := ./temp_info
endif

# Объектные файлы
OBJS := main.o temp_functions.o

# Сборка
all: $(TARGET)
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -s -Wl,--gc-sections -o $@ $^
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