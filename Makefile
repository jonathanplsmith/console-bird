CC=gcc

all: main

main:
	$(CC) -Wall -Wextra -O2 -o bird main.c canvas/consoleCanvas.c

clean:
	rm bird