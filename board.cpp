#include <iostream>
#include <ncurses.h>
#include <stdlib.h>

#include "board.h"
#define MULTIPLIER 1000

Board::Board(){ //default constructor try not to use because it allocates 0 memory
	width = 20;
	height = 20;
	board = (char **) malloc(0);
	score = 0;
}

Board::Board(int iWidth, int iHeight){ //constructor
	width = iWidth;
	height = iHeight;
	board = (char **) malloc(sizeof(char *) * iWidth); //creates a pointer (array) that will contain poiters
	std::cout << "Board Constructed" << std::endl;
	score = 0;
}

Board::Board (const Board& iBoard){ //copy constructor
	width = iBoard.width;
	height = iBoard.height;
	board[iBoard.width][iBoard.height];
	score = iBoard.score;
}

Board::~Board(){
	std::cout << "Board Destructed" << std::endl;
	
	for(int i = 0; i < width; i++) { //free allocoated memomory 
		free(board[i]); //frees each row of the board
	}
	free(board);	//frees the board itself
}

void Board::initBoard(){ //initialize the board with randomness
	for (int i = 0; i < width; i++){
		board[i] = (char *) malloc(sizeof(char) * height*MULTIPLIER); //have to cast to use malloc... also is an array of the board pointer 
		for (int j = 0; j < height; j++){
			board [i][j] = ' ';
		}
	}
}


void Board::drawBoard(){
	clear();
	for (int row = 0; row < height; row++){
		for (int col = 0; col < width; col++){
			printw("%c", board[col][row]);
		}
		printw("\n");
	}
	mvprintw(10, 50, "Score: %d" , score);
	refresh();
}

void Board::drawBorder(){
	int leftSide = 0;
	int rightSide = width-1;
	int topSide = 0;
	int bottomSide = height -1;
	
	for (int col = 0; col < width; col ++){
				board[col][topSide] = '_' ;
				board[col][bottomSide] = '=' ;
	}
	for (int row = 1; row < height; row ++){
		board [leftSide][row] = '|';
		board [rightSide][row] = '|';
	}
	
}

void Board::editBoard(int x, int y, char c){
	board[x][y] = c;
}
