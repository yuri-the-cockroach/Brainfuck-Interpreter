both:
	make build run

run:
	builds/main.o --char --file ./hello_world.bf

build:
	gcc -o builds/bf-run main.c
