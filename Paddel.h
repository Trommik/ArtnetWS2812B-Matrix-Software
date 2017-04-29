#ifndef Paddel_h
#define Paddel_h

#include "PongGame.h"
#include "Vector.h"
#include "Puck.h"

class Paddel
{
 public:

	 void init(bool side);

	 renderData render(int yOff);

	 bool checkCollision(Puck *p);

	 void moveUp();
	 void moveDown();
	 void move(uint8_t y);
	 
	 int getHeight();
	 int getPosY();
	 void setHeight(int h);

 private:

	 Vector pos;
	 int paddelHeight;
	 bool side;

};

extern Paddel rightPlayer;
extern Paddel leftPlayer;

#endif