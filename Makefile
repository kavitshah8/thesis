CC = g++ -O3 

compile: \
src/* thesis/* header_files/* 
	$(CC) src/* thesis/* -o main
