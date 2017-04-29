// 
// Main Class for a Pong game on ws2812b matrixes
// 

#include "PongGame.h"

color paddelCol = { 0, 255, 0 };
color puckCol = { 255, 255, 0 };
color backgroundCol = { 0, 0, 0 };
color scoreLeftCol = { 255, 0, 0 };
color scoreRightCol = { 0, 0, 255 };
color trail1Col = { 170, 170, 0 };
color trail2Col = { 85, 85, 0 };

uint8_t scoreLeft;
uint8_t scoreRight;

void PongGame::set(renderData data)
{
	if (data.x < WIDTH && data.y < HEIGHT) {
		if (data.t == PUCK){
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
		}

		type[data.x][data.y] = data.t;

		renderNeeded = true;
	}
}

void PongGame::removePaddel(int side)
{
	if(side == LEFT_SIDE){ // Left side
		for (int y = 0; y < HEIGHT; y++) {
			for (int x = 0; x < WIDTH; x++) {
				if (type[x][y] == PADDEL_LEFT)
					type[x][y] = BLANK;
			}
		}
	}else if(side == RIGHT_SIDE){
		for (int y = 0; y < HEIGHT; y++) {
			for (int x = 0; x < WIDTH; x++) {
				if (type[x][y] == PADDEL_RIGHT)
					type[x][y] = BLANK;
			}
		}
	}
}

void PongGame::setScore(uint8_t score, bool side)
{
	if(score > WIDTH)
		return;
	if(side == LEFT_SIDE){
		for (int s = 0; s < score; s++){
			type[s][0] = SCORE_LEFT;
		}
	}
	if(side == RIGHT_SIDE){
		for (int s = 0; s < score; s++) {
			type[(WIDTH - 1) - s][WIDTH -1] = SCORE_RIGHT;
		}
	}

	renderNeeded = true;
}

void PongGame::reset()
{
	for (int y = 0; y < HEIGHT; y++) {
		for (int x = 0; x < WIDTH; x++) {
			type[x][y] = BLANK;
		}
	}

	renderNeeded = true;
}

color PongGame::getColor(int x, int y)
{
	switch (type[x][y]){
		case BLANK: 
			return backgroundCol;
		case PUCK:
			return puckCol;
		case PADDEL_LEFT:
			return paddelCol;
		case PADDEL_RIGHT:
			return paddelCol;
		case SCORE_LEFT:
			return scoreLeftCol;
		case SCORE_RIGHT:
			return scoreRightCol;
		case TRAIL1:
			return trail1Col;
		case TRAIL2:
			return trail2Col;
	}
}

int toI(float val)
{
	int i = int(val);
	val = val - int(val);
	if (val > 0.5)
		return i + 1;
	if (-0.5 > val)
		return i - 1;

	return i;
}

PongGame pongGame;