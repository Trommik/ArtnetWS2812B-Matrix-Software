// SnakeGame.h

#ifndef _SNAKEGAME_h
#define _SNAKEGAME_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
	#include "PongGame.h"
	#include "Vector.h"
	#include "deque"
#else
	#include "WProgram.h"
	#include "PongGame.h"
	#include "Vector.h"
	#include "deque"
#endif

#define WIDTH 17 // width in leds of Matrix 
#define HEIGHT 17 // height in leds of Matrix

#define BLANK 0
#define SNAKE_BODY 1
#define APPLE 2
#define SCORE 3
#define SNAKE_HEAD 4
#define SNAKE_END 5

#define UP 1
#define DOWN 2
#define LEFT 3
#define RIGHT 4

#define APPLE_COUNTDOWN_STEPS_MIN 17
#define APPLE_COUNTDOWN_STEPS_MAX 17*2

extern color snakeCol;
extern color appleCol;
extern color scoreCol;

class SnakeGame
{
 public:

	 uint8_t dir;
	 uint8_t length;

	 Vector pos;
	 Vector applePos;
	 
	 boolean renderNeeded = true;


	 void init();
	 void update();
	 void setDir(uint8_t d);
	 void render();
	 void gameOver();

	 color getColor(int x, int y);

 private:
	 uint8_t nextApple;
	 uint8_t type[WIDTH][HEIGHT];

	 std::deque<Vector> snake; // array pointer to store x,y off snake items

	 Vector placeApple();

	 void eat();
	 void edges();
	 void selfCollision();
	 void delPoint(Vector *p);
	 void snakeAdd(uint8_t n);
	 void reset();

};

extern SnakeGame snakeGame;

#endif

