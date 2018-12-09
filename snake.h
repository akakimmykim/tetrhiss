#include <deque>


#ifndef SnakeDefs //prevents overdefining with a precursor
#define SnakeDefs
	#include "board.h"
	#include "food.h"

class Snake{
private:
	int speed;
	char direction;
	
public:
	bool dead; //public so it can be accessed in main easily
		
	std::deque<int> xDeque; //will store the x coordinates
	std::deque<int> yDeque; //will store the y coordinates
	int xLocation;
	int yLocation;
	int bellyCount; //how much the snake has eaten
	int length;

	Snake(); //default constructor
	Snake(int iSpeed); //constructor
	Snake(const Snake& iSnake); //copy constructor
	Snake& operator =(const Snake& iSnake){ //assignment operator
		speed = iSnake.speed;
		length = iSnake.length;
		dead = iSnake.dead;
		bellyCount = iSnake.bellyCount;
		xLocation = iSnake.xLocation;
		yLocation =	iSnake.yLocation;
		xDeque = iSnake.xDeque;
		yDeque = iSnake.yDeque;
	}
	~Snake();
	
	void initSnake(); //puts the first snake coordinates in the deque
	void addSnake();  //modifies coordinates in the deque
	void moveSnake(Board& gBoard); //moves the snake with variant speed
	void drawSnake(Board& gBoard); //draws a snake to the board
	void eraseSnakeTail(Board& gBoard);
	void eatFood(Board& gBoard); //lengthens the snake when it eats a food
	
	void isDead();  //will end the game if method is called by changing dead status
	
	//directional methods
	void moveUp(); 
	void moveDown();
	void moveRight();
	void moveLeft();
	
};

int kbhit();
#endif