CC=gcc
CFLAGS=-Wall -lm -lGL -lGLU -lGLEW -lglfw -lX11 -lXxf86vm -lXrandr -lpthread -lXi -ldl

HEADER = -I./include
LIBB = ./lib/libglfw3.a

all: damage

damage: main.o
	$(CC) main.o -o damage $(LIBB) $(CFLAGS)

main.o: main.c
	$(CC) -c main.c $(HEADER)
clean:
	rm -rf *o  ./damage
