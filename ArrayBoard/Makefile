#add macros
CC=gcc
CFLAGS=-Wall -g -lm

all: game
game: main.o marble.o state.o node.o mcts.o
	$(CC) $(CFLAGS) -o game main.o marble.o state.o node.o mcts.o
main.o: main.c main.h
	$(CC) $(CFLAGS) -c main.c
marble.o: marble.c marble.h
	$(CC) $(CFLAGS) -c marble.c
state.o: state.c state.h marble.h
	$(CC) $(CFLAGS) -c state.c
node.o: node.c node.h
	$(CC) $(CFLAGS) -c node.c
mcts.o: mcts.c mcts.h marble.h node.h state.h
	$(CC) $(CFLAGS) -c mcts.c

clean:
	rm *.o
.PHONY:
	game