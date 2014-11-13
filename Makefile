CC = gcc

compile: \
src/* thesis/* header_files/* 
	$(CC) src/* thesis/* -o main
