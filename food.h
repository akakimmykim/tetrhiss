#ifndef FoodDefs
#define FoodDefs

class Food {
	private:
		int xLocation;
		int yLocation;
	
	public: 
		friend class Snake;
		
		Food(); //default constructor
		Food (int x, int y); //constructor
		Food (const Food& iFood); //copy constructor
		Food& operator = (const Food& iFood){ //assignment operator
			xLocation = iFood.xLocation;
			yLocation = iFood.yLocation;
		}
		~Food();
		void drawFood(Board& gBoard);
};


#endif
