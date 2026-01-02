CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -O2
TARGET = sensor_app

$(TARGET): main.o temp_functions.o
	$(CC) $(CFLAGS) -o $@ $^

main.o: main.c temp_functions.h
	$(CC) $(CFLAGS) -c $<

temp_functions.o: temp_functions.c temp_functions.h
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f *.o $(TARGET)

.PHONY: clean