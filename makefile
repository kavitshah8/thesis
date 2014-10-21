CC = gcc
DEPS = header_files/util.h

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< 

main:
	$(CC) -c src/util.c thesis/main.c
	$(CC) util.o main.o -o main 