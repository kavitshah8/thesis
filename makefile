CC = gcc

exec:
	./main

compile: \
src/* thesis/* 
	$(CC) src/* thesis/* -o main
	echo "compiling"
	touch compile 