// 
// 
// 

#include "SnakeGame.h"

color snakeCol = { 0, 255, 0 };
color appleCol = { 255, 0, 0 };
color scoreCol = { 0, 0, 255 };


color SnakeGame::getColor(int x, int y)
{
	switch (type[x][y]) {
	case BLANK:
		return backgroundCol;
	case SNAKE_BODY:
		return snakeCol;
	case SNAKE_HEAD:
		return snakeCol;
	case SNAKE_END:
		return snakeCol;
	case APPLE:
		return appleCol;
	case SCORE:
		return scoreCol;
	}
}

void SnakeGame::init()
{
	pos = Vector(random(WIDTH), random(HEIGHT));

	length = 1; // 1additional piece so the snake now has 2 pieces
	snake.resize(length);

	dir = random(1,5);
	Serial.println(dir);

	applePos = placeApple();

}


Vector SnakeGame::placeApple()
{
	Vector newPos = Vector(int(random(WIDTH)), int(random(HEIGHT)));
	while (newPos.x < 0 || newPos.y < 0 || newPos.x >= WIDTH || newPos.y >= HEIGHT) {
		newPos = Vector(int(random(WIDTH)), int(random(HEIGHT)));
		nextApple = random(APPLE_COUNTDOWN_STEPS_MIN, APPLE_COUNTDOWN_STEPS_MAX); // ###TODO### Check that the apple is not in the snake 
	}

	return newPos;
}


void SnakeGame::delPoint(Vector *p)
{
	type[int(p->x)][int(p->y)] = BLANK;
}

void SnakeGame::update()
{

	nextApple--;

	if (nextApple <= 0){
		delPoint(&applePos);
		applePos = placeApple();
	}
	
	if (length > 0) {
		if (length == snake.size() && !(length == 0)) {
			delPoint(&snake[snake.size()-1]); // del last element from render
			snake.pop_back(); // del last element
		}
		snake.push_front(pos); // set pos to the first element 
	}
	
	if (dir == UP) pos.y -= 1;
	else if (dir == DOWN) pos.y += 1;
	else if (dir == LEFT) pos.x -= 1;
	else if (dir == RIGHT) pos.x += 1;

	edges();

	selfCollision();

	eat();

	renderNeeded = true;
}

void SnakeGame::selfCollision()
{
	for(int i = 0; i < length; i++){
		if (pos.x == snake[i].x && pos.y == snake[i].y)
			gameOver();
	}
}

void SnakeGame::edges()
{
	if (!(pos.x >= 0 && pos.y >= 0 && pos.x < WIDTH && pos.y < HEIGHT)) {
		gameOver();
	}
}


void SnakeGame::gameOver()
{
	snake.clear();
	reset();

	init();
}


void SnakeGame::eat()
{
	if (pos.x == applePos.x && pos.y == applePos.y){
		delPoint(&applePos);

		snakeAdd(3);

		applePos = placeApple();
	}
}


void SnakeGame::snakeAdd(uint8_t n)
{
	length += n;
	snake.resize(length);
}


void SnakeGame::setDir(uint8_t d)
{
	if (dir < 5 && dir > 0)
		dir = d;
}


void SnakeGame::render()
{
	uint8_t appleID = APPLE;
	uint8_t snakeHeadID = SNAKE_HEAD;
	uint8_t snakeEndID = SNAKE_END;
	uint8_t snakeID = SNAKE_BODY;

	type[int(applePos.x)][int(applePos.y)] = appleID;
	type[int(pos.x)][int(pos.y)] = snakeHeadID;

	renderNeeded = true;
}

void SnakeGame::reset()
{
	for (int y = 0; y < HEIGHT; y++) {
		for (int x = 0; x < WIDTH; x++) {
			type[x][y] = BLANK;
		}
	}

	renderNeeded = true;
}

SnakeGame snakeGame;

