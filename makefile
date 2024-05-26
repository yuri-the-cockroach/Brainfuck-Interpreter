both:
	make build run

run:
	LD_LIBRARY_PATH=$(shell pwd)/libs ./main.o test.bf

build:
	gcc -o main.o main.c -g3 -Wall
