both:
	make build run

run:
	builds/main.o --char --file ./hello_world.bf

build:
	gcc -o builds/main.o main.c -O0 -g3 -Wall
