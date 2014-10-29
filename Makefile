CC = gcc

exec:
	./main
	compile

compile: \
src/* thesis/* 
	$(CC) src/* thesis/* -o main
