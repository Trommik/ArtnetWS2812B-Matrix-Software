// 
// 
// 

#include "SnakeGame.h"

color snakeCol = { 85, 85, 0 };
color appleCol = { 85, 85, 0 };
color scoreCol = { 85, 85, 0 };

uint8_t score;

void SnakeGame::set(renderData data)
{
	if (data.x < WIDTH && data.y < HEIGHT) {
		/*if (data.t == Snake) {
			for (int y = 0; y < HEIGHT; y++) {
				for (int x = 0; x < WIDTH; x++) {
					if (type[x][y] == PUCK)
						type[x][y] = BLANK;
					if (type[x][y] == TRAIL1)
						type[x][y] = BLANK;
					if (type[x][y] == TRAIL2)
						type[x][y] = BLANK;
				}
			}
		}*/

		type[data.x][data.y] = data.t;

		renderNeeded = true;
	}
}

void SnakeGame::setScore(uint8_t score)
{
	//if (score > WIDTH)
	//	return;
	//if (side == LEFT_SIDE) {
	//	for (int s = 0; s < score; s++) {
	//		type[s][0] = SCORE_LEFT;
	//	}
	//}
	//if (side == RIGHT_SIDE) {
	//	for (int s = 0; s < score; s++) {
	//		type[(WIDTH - 1) - s][WIDTH - 1] = SCORE_RIGHT;
	//	}
	//}

	//renderNeeded = true;
}

color SnakeGame::getColor(int x, int y)
{
	switch (type[x][y]) {
	case BLANK:
		return backgroundCol;
	case SNAKE:
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

	length = 2;

	dir = random(4);

	/*AddSnakeItem = false;
	AppleCount = false;*/

	placeApple(&pos);

}

void SnakeGame::placeApple(Vector *p)
{
	if (pos.x > 0 && pos.y > 0 && pos.x <= WIDTH && pos.y <= HEIGHT) {
		nextApple = random(APPLE_COUNTDOWN_STEPS_MIN, APPLE_COUNTDOWN_STEPS_MAX); // ###TODO### Check that the apple is not in the snake 
	}
}

void SnakeGame::update()
{
	type[pos.x][pos.y] = APPLE;

	edges();

	if (dir == UP) pos.y -= 1;
	else if (dir == DOWN) pos.y += 1;
	else if (dir == LEFT) pos.x -= 1;
	else if (dir == RIGHT) pos.x += 1;

}

boolean SnakeGame::edges()
{
	if (pos.y < 0 || pos.y > HEIGHT - 1) { // top or bottom side of window
		// ###TODO### GameOver!!!
		return false;
	}else if (pso.x < 0 || pos.x > WIDTH -1){
		// ###TODO### GameOver!!!

	}
}

SnakeGame snakeGame;

