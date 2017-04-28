// SnakeGame.h

#ifndef _SNAKEGAME_h
#define _SNAKEGAME_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "PongGame.h"
#include "Vector.h"

#define WIDTH 17 // width in leds of Matrix 
#define HEIGHT 17 // height in leds of Matrix

#define BLANK 0
#define SNAKE 1
#define APPLE 2
#define SCORE 3
#define HEAD 4
#define END 5

#define UP 0
#define DOWN 1
#define LEFT 2
#define RIGHT 3

#define APPLE_COUNTDOWN_STEPS_MIN 17
#define APPLE_COUNTDOWN_STEPS_MAX 17*2

extern color snakeCol;
extern color appleCol;
extern color scoreCol;

extern uint8_t score;

class SnakeGame
{
 public:

	 uint8_t dir;
	 Vector pos;
	 uint8_t length;

	 boolean renderNeeded = true;

	 void set(renderData Data);
	 void setScore(uint8_t score);

	 void init();
	 void placeApple(Vector *p);

	 color getColor(int x, int y);

 private:

	 uint8_t type[WIDTH][HEIGHT];

};

extern SnakeGame snakeGame;

#endif

