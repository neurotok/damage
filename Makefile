CC=gcc
CFLAGS=-Wall -lm -lGL -lGLU -lGLEW -lglfw -lX11 -lXxf86vm -lXrandr -lpthread -lXi -ldl

HEADER = -I./include
LIBB = ./lib/libglfw3.a

all: main

main: main.o
	$(CC) main.o -o main $(LIBB) $(CFLAGS)

main.o: main.c
	$(CC) -c main.c $(HEADER)
clean:
	rm -rf *o main
