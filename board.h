#ifndef BoardDef
#define BoardDef

#define XMAX 500
#define YMAX 500



class Board {
private:
	int width;
	int height;
	char **board; //was forced to use pointers to make dynamic allocation of memory possible... the size of an array can't be changed later

public:
	friend class Snake; //allows snake to access the board array
	friend class Food; //allows food to access the board array
	friend class Tetris; //allows food to edit the board array
	
	int score; //used to collect and display scores.
	
	Board(); //default constructor
	Board(int iWidth, int iHeight); //constructor
	Board(const Board& iBoard); //copy constructor
	Board& operator = (const Board& iBoard){ //assignment operator
		width = iBoard.width;
		height = iBoard.height;
	}
	~Board(); //destructor
	
	void initBoard();
	void drawBoard();
	void drawBorder();
	void editBoard(int x, int y, char Char);
};

#endif
