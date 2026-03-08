# Компилятор и флаги
CC = gcc
CFLAGS = -std=c99 -Wall -Wextra -pedantic -O3 -g
LDFLAGS = -lncurses

# Имена файлов
TARGET = area_calc
SRCS = menu.c run_menu.c math_lib.c
OBJS = $(SRCS:.c=.o)
HEADERS = run_menu.h math_lib.h

# Цели
.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)
# раскоментировать для автоматического удаления .o файолов:
#	rm -f $(OBJS)  # <-- Удаляем .o файлы сразу после успешной линковки
#	@echo "✅ Сборка завершена, .o файлы удалены"

# Правило компиляции .c в .o
%.o: %.c run_menu.h
	$(CC) $(CFLAGS) -c $< -o $@

# Явные зависимости для пересборки при изменении заголовков
menu.o: menu.c run_menu.h math_lib.h
run_menu.o: run_menu.c run_menu.h math_lib.h
math_lib.o: math_lib.c math_lib.h


clean:
	rm -f $(OBJS) $(TARGET)
	@echo "✅ Файлы удалены"
