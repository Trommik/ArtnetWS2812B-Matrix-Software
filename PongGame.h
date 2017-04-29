// PongGame.h

#ifndef _PLAYFIELD_h
#define _PLAYFIELD_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#define WIDTH 17 // width in leds of Matrix 
#define HEIGHT 17 // height in leds of Matrix

#define START_PADDEL_HEIGHT 5 // default height of paddels at start

#define SPEED 1
#define ANGLE 65

#define RIGHT_SIDE 0
#define LEFT_SIDE 1

#define LED_PIN 6 // Which pin on the Arduino is connected to the NeoPixels
#define NUM_LEDS 289 // How many NeoPixels are attached to the Arduino normaly WIDTH*HEIGHT

#define BLANK 0
#define PUCK 1
#define PADDEL_LEFT 2
#define PADDEL_RIGHT 3
#define SCORE_LEFT 4
#define SCORE_RIGHT 5
#define TRAIL1 6
#define TRAIL2 7

struct color
{
	uint8_t r;
	uint8_t g;
	uint8_t b;
}; // struct for RGB Color

struct renderData
{
	int x, y;
	uint8_t t;
}; // struct for Rendering the objects //#TODO: Make this better

extern color paddelCol;
extern color puckCol;
extern color backgroundCol;
extern color scoreLeftCol;
extern color scoreRightCol;
extern color trail1Col;
extern color trail2Col;

extern uint8_t scoreLeft;
extern uint8_t scoreRight;

class PongGame
{
 public:

	boolean renderNeeded = true;

	//void set(int x, int y, color c);
	void set(renderData Data);
	void setScore(uint8_t score, bool side);
	void reset();

	void removePaddel(int side);

	color getColor(int x, int y);

 private:

	uint8_t type[WIDTH][HEIGHT]; 

};

extern PongGame pongGame;

int toI(float val);

#endif

