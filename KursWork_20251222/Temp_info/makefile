#makefile
all: temp_info.exe

temp_info.exe: main.o temp_functions.o
	gcc -o temp_info.exe main.o temp_functions.o

main.o: main.c temp_functions.h
	gcc -c main.c

temp_functions.o: temp_functions.c temp_functions.h
	gcc -c temp_functions.c

clean:
	rm -f *.o temp_info.exe

run: temp_info.exe
	./temp_info -h