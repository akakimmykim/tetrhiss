#ifndef TETDef
#define TETDef

class Tetris {
private:
	int speed;
	char direction;
	bool hasStopped;
	bool lrClear;
	
public:	
	Tetris();
	Tetris(int iSpeed);
	Tetris(const Tetris& iTetris);
	~Tetris();
	Tetris& operator =(const Tetris& iTetris){
		speed = iTetris.speed;
		direction = iTetris.direction;
		hasStopped = iTetris.hasStopped;
		lrClear = iTetris.lrClear;
	}
	
	void dropShape(Snake& s, Board& gBoard);
	void drawTetris(Snake& s,Board& gBoard, char T);
	void clearLine(Board& gboard);
	void checkObstruction(Snake& s, Board& gBoard);
	void checkSides(Snake& s, Board& gBoard);
	void moveDown(Board& gBoard, int startingRow);
	void exitT();
	
	//movements
	void drop(Snake& s, Board& gBoard);
	void moveRight(Snake&s, Board& gBoard);
	void moveLeft(Snake&s, Board& gBoard);

};

#endif