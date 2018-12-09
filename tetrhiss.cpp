#include <iostream>
#include <ncurses.h>
#include <time.h>

#ifndef FinDef
#define FinDef
	
	#include "tetrhiss.h"

int main(){
	
	
	std::srand(time(nullptr)); //srand initializes a random sequence based on time
	
	//begins ncurses programming
	initscr(); 
	cbreak(); //makes it so that there is a one time input
	noecho();
	
	if(!has_colors()){ //safeguards against computers that can't support ncurses color
		printw("Terminal does not support color");
		getch();
		return -1;
	}	
	
	//intro to game
	startGame();

	//run game
	int on = 1; //0 is off 1 is on
	while(on == 1) { //runs the game for the first time
		playGame(on);
	}
	
	while(1){ //used if player wishes to play again
		clear();
		printw("\nPlay again?\n1 to play again");
		refresh();
		getch();
		int pAgain = getch();
		pAgain -= 48;
		if (pAgain == 1){
			on = 1;
			while(on == 1) {
				playGame(on);
			}
		}
		else {
			clear();
			betterPrint("Play again some other time ;)");
			break;
		}
	}

	endwin();
}


#endif