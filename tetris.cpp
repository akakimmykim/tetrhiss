#include <iostream>
#include <ncurses.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/types.h>

#ifndef TetrisDef
#define TetrisDef
	#include "snake.h"
	#include "tetris.h"

#define MAXWAIT 200000
#define FULL 4

Tetris::Tetris(){ //default constructor
	speed = MAXWAIT-100000;
	direction = 'd'; //does not have direction until user input
	hasStopped = false;
	lrClear = true;
}

Tetris::Tetris(int iSpeed){ //constructor
	speed = iSpeed;
	direction = 'd';
	hasStopped = false;
	lrClear = true;
}

Tetris::Tetris(const Tetris& iTetris){ //copy constructor
	speed = iTetris.speed;
	direction = iTetris.direction;
	hasStopped = iTetris.hasStopped;
	lrClear = iTetris.lrClear;
}

Tetris::~Tetris(){ //destructor
	std::cout << "Tetris destroyed" << std::endl;
}

void Tetris::drawTetris(Snake& s, Board& gBoard, char T){  //draws the tetris on the board
	clear();
	int i;
	for (i = 0; i < s.length; i++){
		gBoard.editBoard(s.xDeque[i], s.yDeque[i], T);
	}
	gBoard.drawBoard(); //draws the tetris
}	

void Tetris::dropShape(Snake& s, Board& gBoard) {  //drops the shape
	int i;

	while (hasStopped == false){	
		if (kbhit()){
			char keyPressed = getchar();
			switch(keyPressed){  //change direction
				case ' ': drop(s, gBoard);
					break;
				case 'd': moveRight(s, gBoard), direction = 'r';
					break;
				case 'a': moveLeft(s, gBoard), direction = 'l';
					break;
			}
		}
		
		checkObstruction (s, gBoard); //checks if shape can move down
		if (hasStopped == false){ //if no obstruction, will move down
			for (i = 0; i < s.length; i++){
				gBoard.editBoard(s.xDeque[i],s.yDeque[i], ' '); //erases original
				s.yDeque[i] += 1;
			}
			
			drawTetris(s, gBoard, 'o'); 
			usleep(MAXWAIT - speed*9000); //drop speed
		}	
	}
	
	clearLine(gBoard); //clears line
}

void Tetris::checkObstruction(Snake& s, Board& gBoard){
	int i;
	
	for (i = 0; i < s.length ; i++){ //checks to see if below is available
		int yBelow = s.yDeque[i] + 1;
		hasStopped = !((gBoard.board[s.xDeque[i]][yBelow] != 'S') && 
		(gBoard.board[s.xDeque[i]][yBelow] != '='));

		if (hasStopped == true){
			drawTetris(s, gBoard, 'S'); //converts 'o' to 'S'
			break;
		}
	}
}

void Tetris::checkSides(Snake& s, Board& gBoard){
	int i;
	
	for (i = 0; i < s.length; i++){
		int Right = s.xDeque[i] + 1;
		int Left = s.xDeque[i] - 1;
		//if statement to make sure lrClear is not overwritten
		if (direction == 'r'){ //will run if moving right
			lrClear = !((gBoard.board[Right][s.yDeque[i]] == '|') ||
						(gBoard.board[Right][s.yDeque[i]] == 'S'));
		}
		else if (direction == 'l'){ //will run if moving left
			lrClear = !((gBoard.board[Left][s.yDeque[i]] == '|') ||
						(gBoard.board[Left][s.yDeque[i]] == 'S'));
		}
		if (lrClear == false){ //will exit loop if there is an obstruction
			break;
		}
	}
} 
void Tetris::clearLine(Board& gBoard){
	int row;
	int col;
	//everything below happens per row
	for (row = 1; row < gBoard.height-1; row++){ //i=1 and the '-1' ignores borders
		int space = gBoard.width-2; //keeps count of spaces/row
		// moves through every column (x value) between borders
		for (col=1; col < gBoard.width-1; col++){ //i=1 and the '-1' ignores side borders
			//runs if there is a space
			if (gBoard.board[col][row] != ' '){
				space --; //decreases space
				if (space == 0){ //runs if no spaces within border
					moveDown(gBoard, row); //clears old rows	
					gBoard.score *= 2;
				}
			}
		 }
	 }
}

void Tetris::moveDown(Board& gBoard, int startingRow){
	
	int TOP = gBoard.height-1;
	int ABOVE = gBoard.height-startingRow;
	//loops through rows above clear (inclusive of row) 
	//and moves each row above down. 'i' begins on checking row
	for (int i = 0; i < ((TOP)-(ABOVE)) ; i++){
		for (int x = 1; x < gBoard.width-1; x++){
 			/* 	printw("changing:-%c- to -%c-\t", 
				gBoard.board[x][startingRow-i],gBoard.board[x][startingRow-i-1]);
				refresh();
				getchar();   */
			gBoard.editBoard(x,startingRow-i, gBoard.board[x][startingRow-i-1]);
			
		}
		gBoard.drawBoard();
	}
	gBoard.drawBoard();
}
void Tetris::exitT(){
	hasStopped = true;
}

void Tetris::drop(Snake&s, Board& gBoard){
	int temp = speed;
	speed = MAXWAIT;
	dropShape(s, gBoard);
	speed = temp;
}

void Tetris::moveRight(Snake&s, Board& gBoard){ //moves snake right
	int i;
	checkSides(s, gBoard);
	if (lrClear == true){
		for (i=0; i < s.length; i++){
			gBoard.editBoard(s.xDeque[i],s.yDeque[i], ' '); //deletes previous spot
			s.xDeque[i] += 1;
		}
	}
}

void Tetris::moveLeft(Snake&s, Board& gBoard){
	int i;
	checkSides(s, gBoard);
	if (lrClear == true){
		for (i=0; i < s.length; i++){
			gBoard.editBoard(s.xDeque[i],s.yDeque[i], ' '); //deletes previous spot
			s.xDeque[i] -= 1;
		}
	}
}

#endif	
