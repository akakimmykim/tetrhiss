#include <iostream>
#include <ncurses.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/types.h>
#include <cstdlib>
#include <ctime>

#include "snake.h"
#include "food.h"

Food::Food(){  //default constructor
	xLocation = 0;
	yLocation = 0;
}

Food::Food (int x, int y){ //constructor
	xLocation = x;
	yLocation = y;
}

Food::Food (const Food& iFood){ //copy constructor
	xLocation = iFood.xLocation;
	yLocation = iFood.yLocation;
}

Food::~Food(){
	std::cout << "Food destroyed" << std::endl;
}
		
void Food::drawFood(Board& gBoard){		//draws a food piece on the board array
	
	xLocation = rand() % (gBoard.width-2); 		//xrand is a random number between 0 and xMax
	yLocation = rand () % (gBoard.height-2);	//yrand is a random number between 0 and yMax
	xLocation += 1; //prevents food from spawning on the border
	yLocation += 1;
	while (gBoard.board [xLocation][yLocation] != ' '){ //food cannot spawn on taken pieces
			xLocation = rand() % (gBoard.width-2); 		//xrand is a random number between 0 and xMax
		yLocation = rand () % (gBoard.height-2);	//yrand is a random number between 0 and yMax
		xLocation += 1; //prevents food from spawning on the border
		yLocation += 1;
	}
	
	gBoard.editBoard(xLocation,yLocation,'F');
	gBoard.drawBoard();
}
