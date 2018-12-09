#include <iostream>
#include <ncurses.h>
#include <unistd.h>

#include "snake.h"
#include "tetris.h"
#include "food.h"
#include "board.h"
#include "gameplay.h"

void betterPrint (std::string statement){
	printw(statement.c_str()); //c_str converts variable to string
	refresh();
	sleep(1);
}

void startGame(){	
	
	start_color(); //enables colors
	init_pair(1, COLOR_GREEN, COLOR_BLACK); 
	attron(A_BOLD); //enables attribute usage (BOLD)
	attron(COLOR_PAIR(1)); //green and black color pair made
	printw("TETRHISS~\nThe tetrHISSSSSSS wombo combo\n"); //name of the game
	printw("\nHow to Play");
	attroff(COLOR_PAIR(1)); //color turned off
	attroff(A_BOLD);
	
	//instructions
	printw("\n1. The first part is your favortie game, Tetris");
	printw("\n2.Once your snake eats 4 pieces of Food, whatever shape you end up with will be your tetris shape");
	printw("\n3.Your goal is rack them points");
	printw("\n4.WASD moves the snake!");
	printw("\n5. You can up the difficulty if it is too easy for you");
	printw("\n6. You can't turn the tetris shape, so make your snake beautiful!");
	printw("\n7. The Food can spawn in tight places and even closed places!\nThe more you mess up early, the easier it will be for you to FAIL!");	
	printw("\n\nPress any button to play");
	refresh();
	getch();
	clear();
}

void chooseVariables(int vArray[]){
	echo();
	clear();
	//snake moving speed
	betterPrint("What difficulty of Snake?\n 0(VERY SLOW)-9(OP!)\n");
	int sSpeed = getch();
	vArray[0] = sSpeed-48;
	
	//tetris falling speed
	betterPrint("\nWhat difficulty of Tetris?\n 0(Easiest)-9(Hardest)\n");
	int tSpeed = getch();
	vArray[1] = tSpeed-48;
	
	//width and height of the board
	betterPrint("\nHow big do you want the board?\n 0:small 1:medium 2:large\nMedium is easiest\n");
	int size = getch() - 48;
	int bWidth, bHeight;
	
	switch (size){
		case 0: bWidth = 15, bHeight = 25;
			break;
		case 1: bWidth = 20, bHeight = 40;
			break;
		case 2: bWidth = 40, bHeight = 50;
			break;
		default: bWidth = 20, bHeight = 40;

	} 
	vArray[2] = bWidth;
	vArray[3] = bHeight;
	
}

int playGame(int& on){
	int vArray[4];
	//choose variables	
	echo(); //renable user to see what they input for variables
	chooseVariables(vArray); //choose speeds and board size
	noecho();
	
		// initialize the board
		Board gameB(vArray[2],vArray[3]); //initializes an instance gameB with a width and height of 20 chars
		gameB.initBoard(); //initializes the board with 'a's 
		gameB.drawBorder();
		gameB.drawBoard(); //draws board using printw
	
	while (on == 1){
		Food f1; //initialize the food
		f1.drawFood(gameB); //draws out the food
		Snake s1(vArray[0]); //initialize the snake: speed, length, col, row
		s1.initSnake();
		s1.drawSnake(gameB); //draws the snake
		s1.moveSnake(gameB);
		if (s1.dead == true){
			on = 0;
		}
		else{
			Tetris t1(vArray[1]);
			t1.drawTetris(s1, gameB, 'o');
			t1.dropShape(s1, gameB); 
		}
	}
}
