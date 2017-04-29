#include "Paddel.h"

void Paddel::init(bool _side)
{
	if(_side == LEFT_SIDE)
		pos.x = 0;
	if(_side == RIGHT_SIDE)
		pos.x = WIDTH-1;

	pos.y = HEIGHT/2-START_PADDEL_HEIGHT/2;
	paddelHeight = START_PADDEL_HEIGHT;
	side = _side;

	for (int off = 0; off < rightPlayer.getHeight(); off++) {
		pongGame.set(rightPlayer.render(off));
		pongGame.set(leftPlayer.render(off));
	}

}

renderData Paddel::render(int yOff)
{
	uint8_t type;
	if(side == LEFT_SIDE)
		type = PADDEL_LEFT;
	if(side == RIGHT_SIDE)
		type = PADDEL_RIGHT;

	renderData data = {int(pos.x), int(pos.y)+yOff, type};
	return data;
}

bool Paddel::checkCollision(Puck * p)
{
	if (side == LEFT_SIDE) { // linkes oder rechts paddel   pos.x == 0
		if ((p->pos.x + p->vel.x <= pos.x + 0.5) &&
			 ((p->pos.y + p->vel.y >= pos.y - 0.5) &&
			  (p->pos.y + p->vel.y < pos.y + paddelHeight + 0.5 ))) { // check Paddel

			return true;
		}
	} else if (side == RIGHT_SIDE) { // linkes oder rechts paddel   pos.x == 16
		if ((p->pos.x + p->vel.x > pos.x - 0.5) && 
			 ((p->pos.y + p->vel.y >= pos.y + 0.5) && 
			  (p->pos.y + p->vel.y < pos.y + paddelHeight + 0.5))) { // check Paddel

			return true;
		}
	}
	return false;
}

void Paddel::moveUp()
{
	pos.y -= 1;
	if(pos.y < 0)
		pos.y = 0;
	Serial.println(pos.y);
}

void Paddel::moveDown()
{
	pos.y += 1;
	if (pos.y + paddelHeight > HEIGHT - 1)
		pos.y = HEIGHT - paddelHeight;
	Serial.println(pos.y);
}

void Paddel::move(uint8_t y)
{
	pos.y = y;

	/*if (pos.y + paddelHeight < HEIGHT)
		pos.y = HEIGHT - paddelHeight;
	if (pos.y < 0)
		pos.y = 0;*/
}

int Paddel::getHeight()
{
	return paddelHeight;
}

int Paddel::getPosY()
{
	return int(pos.y);
}

void Paddel::setHeight(int h)
{
	paddelHeight = h;
}

Paddel rightPlayer;
Paddel leftPlayer;