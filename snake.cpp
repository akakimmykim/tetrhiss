#include <iostream>
#include <ncurses.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/types.h>

#include "snake.h"
#include "board.h" //uses the instance of a board as many arguments

#define MAXWAIT 170000
#define FULL 4



Snake::Snake(){ //default constructor
	speed = 1;
	length = rand()%5 + 1;
	dead = false;
	direction = 'r';
	bellyCount = 0;
	xLocation = length + 1;
	yLocation = 2;
	xDeque;
	yDeque;
}

Snake::Snake(int iSpeed){ //constructor
	speed = iSpeed;
	length = rand()%5 + 1;
	dead = false;
	direction = 'r';
	bellyCount = 0;
	xLocation = length+1;
	yLocation = 2;
	xDeque;
	yDeque;
}

Snake::Snake (const Snake& iSnake){ //copy constructor
	speed = iSnake.speed;
	length = iSnake.length;
	dead = iSnake.dead;
	direction = iSnake.direction;
	bellyCount = iSnake.bellyCount;
	xLocation = iSnake.xLocation;
	yLocation =	iSnake.yLocation;
}

Snake::~Snake () {
	std::cout << "Snake destructed" << std::endl;
}

void Snake::initSnake(){ //creates the x and y deque to hold the snake coordinates
		for (int i = 0; i < length; i++){
			xDeque.push_back(xLocation-i);
			yDeque.push_back(yLocation);
		}
}

void Snake::addSnake(){
	xDeque.push_front(xLocation);
	yDeque.push_front(yLocation);
}

void Snake::moveSnake (Board& gBoard){

	while (dead == false && bellyCount < FULL) { //will run this loop while the snake is alive!
		if(kbhit()){
			char keyPressed = getch();
			//stops snake from eating itself 
			if ((direction == 'r' && keyPressed == 'a')||(direction == 'l' && keyPressed == 'd')){
				printw("\nYou killed yourself");
				isDead();
			}
			else if ((direction == 'u' && keyPressed == 's')||(direction == 'd' && keyPressed == 'w')){
				printw("\nYou killed yourself");
				isDead();	
			}
			
			switch(keyPressed){  //change direction
				case 'd': moveRight();
					break;
				case 'a': moveLeft();
					break;
				case 'w': moveUp();
					break;
				case 's': moveDown();
					break;
			}
		}
	
		switch(direction){ //shifts the x and y coordinate
			case 'r': xLocation ++; //moves one char space at a time
				break; 
			case 'l': xLocation --;
				break;
			case 'u': yLocation --;
				break;
			case 'd': yLocation ++;
				break;
			default: 
				isDead();
		}
		
		addSnake();
		drawSnake(gBoard);
		
		usleep(MAXWAIT - speed*9000); //controls the speed of the snake
		
	}		
}

void Snake::drawSnake(Board& gBoard){  //draws the snake on the board
	clear();
	if (gBoard.board[xLocation][yLocation] == 'F'){ // if it eats food
		eatFood(gBoard);
	}
	else if (gBoard.board[xLocation][yLocation] == ' '){
		for (int i = 0; i < length; i++){
			if (i == 0){
				gBoard.editBoard(xDeque[i], yDeque[i], '0'); //Draws the Snake
			}
			else{
				gBoard.editBoard(xDeque[i], yDeque[i], 'o');
				
			}
		}
		gBoard.drawBoard(); //draws the snake
		eraseSnakeTail(gBoard);
	}
	else {
		isDead();
	}
}	

void Snake::eraseSnakeTail(Board& gBoard){
	gBoard.editBoard(xDeque.back(), yDeque.back(), ' '); //deletes the snake tail
	xDeque.pop_back();
	yDeque.pop_back();
}


void Snake::eatFood(Board& gBoard){
	gBoard.score ++;
	bellyCount ++; //increases the count on food and makes extra food isn't created
	if(bellyCount < FULL){
		Food* newFood = new Food();
		newFood->drawFood(gBoard);
	}

	length ++;
}

void Snake::isDead(){
	sleep(1); //shows the death
	dead = true;
	attron(A_BOLD);
	mvprintw(20,20, "Game over!");
	attroff(A_BOLD);
	refresh();
	sleep(1);
	clear();
}

void Snake::moveUp(){
	direction = 'u';
}

void Snake::moveDown(){
	direction = 'd';
}
void Snake::moveRight(){
	direction = 'r';
}

void Snake::moveLeft(){
	direction = 'l';
}



int kbhit () {   //check if key is pressed (GOT FROM ONLINE)
  struct timeval tv;
  fd_set read_fd;

  tv.tv_sec=0;
  tv.tv_usec=0;
  FD_ZERO(&read_fd);
  FD_SET(0,&read_fd);

  if(select(1, &read_fd, NULL, NULL, &tv) == -1)
    return 0;

  if(FD_ISSET(0,&read_fd))
    return 1;

  return 0;
}
