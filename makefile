CC=g++
CFLAGS=-I.

all: game

game: tetrhiss.o board.o food.o snake.o tetris.o gameplay.o
	$(CC) $(CFLAGS) tetrhiss.o board.o food.o snake.o tetris.o gameplay.o -lncurses -o game

tethriss.o: tetrhiss.cpp tetrhiss.h
	$(CC) $(CFLAGS) -c tetrhiss.cpp -lncurses
	
board.o: board.cpp board.h
	$(CC) $(CFLAGS) -c board.cpp -lncurses

snake.o: snake.cpp snake.h
	$(CC) $(CFLAGS) -c snake.cpp -lncurses

food.o: food.cpp food.h
	$(CC) $(CFLAGS) -c food.cpp -lncurses
	
tetris.o: tetris.cpp tetris.h
	$(CC) $(CFLAGS) -c tetris.cpp -lncurses
	
gameplay.o: gameplay.cpp gameplay.h
	$(CC) $(CFLAGS) -c gameplay.cpp -lncurses
	
clean:
	rm -rf *o make

