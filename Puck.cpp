// 
// Class for a pong puck
// 

#include "Puck.h"

void Puck::init()
{
	speed = SPEED;
	maxAng = ANGLE;

	pos = Vector(WIDTH/2, HEIGHT/2);
	vel = Vector(newVel(random(0,1)));
}

renderData Puck::render()
{
	renderData data = { toI(pos.x), toI(pos.y), PUCK };

	puckRenderData[0] = data;

	return data;

}

renderData Puck::renderLast()
{
	return puckRenderData[1];
}

renderData Puck::renderLastLast()
{
	return puckRenderData[2];
}

void Puck::update()
{
	edges();

	if (rightPlayer.checkCollision(&puck))
		puck.vel.x *= -1;
	if (leftPlayer.checkCollision(&puck))
		puck.vel.x *= -1;

	pos.add(vel);

	puckRenderData[2] = puckRenderData[1];
	puckRenderData[1] = puckRenderData[0];

	if (puckRenderData[1].t == PUCK)
		puckRenderData[1].t = TRAIL1;

	if (puckRenderData[2].t == TRAIL1)
		puckRenderData[2].t = TRAIL2;
}

void Puck::edges()
{
	if (pos.y + vel.y < 0.5 / 2 || pos.y + vel.y > HEIGHT - 1 - 0.5 / 2) { // top or bottom side of window
		vel.y *= -1; // inverts the y velosity so the ball bounce off the edge
	}

	if (pos.x + vel.x < -0.5/2) { // leftside of window
		//vel.x *= -1;
		pos = Vector(WIDTH / 2, HEIGHT / 2);
		vel = Vector(newVel(RIGHT_SIDE));
		scoreRight += 1;
		if(scoreRight > WIDTH)
			scoreRight = 0;
		pongGame.setScore(scoreRight, RIGHT_SIDE); // right side = top side
	}

	if (pos.x + vel.x > (WIDTH + 0.5 / 2)) { // rightside of window
		//vel.x *= -1;
		pos = Vector(WIDTH / 2, HEIGHT / 2);
		vel = Vector(newVel(LEFT_SIDE));
		scoreLeft += 1;
		if (scoreLeft > WIDTH)
			scoreLeft = 0;
		pongGame.setScore(scoreLeft, LEFT_SIDE); // left side = bottom side
	}
}
/*
Vector Puck::newVel(bool side)
{
	Vector newVel;
	
	if (side == LEFT_SIDE) { // suche neue richtung wenn richtung = alteRichtung oder Richtung.y = 0 oder ball bewegt sich nach rechts
		//newVel = Vector(float(radians(ANGLE)));
		//newVel.x = -newVel.x;
		newVel = Vector(-1, 1);
		if(random(0,2))
			newVel.y = -newVel.y;
	}else if (side == RIGHT_SIDE) { // suche neue richtung wenn richtung = alteRichtung oder Richtung.y = 0 oder ball bewegt sich nach links
		//newVel = Vector(float(radians(ANGLE)));
		newVel = Vector(1,1);
		if (random(0, 2))
			newVel.y = -newVel.y;
	}

	//float n = 1 / newVel.x;
	//newVel.mult(n); // makes the vel.y and vel.x to an number without float 

	return newVel;
}
*/


bool Puck::checkVel(Vector *v) {
	float heading = degrees(v->heading());

	if (heading == -180.00)
		return false;
	if (heading == 0.00)
		return false;

	if (((heading > maxAng) && (heading <= 180 - maxAng)) || ((heading >= maxAng - 180) && (heading < -maxAng))) {
		return false;
	}
	return true;
}

bool Puck::checkVel(Vector *v, bool side) {
	float heading = degrees(v->heading());

	if (heading == -180.00)
		return false;
	if (heading == 0.00)
		return false;

	if (((heading > maxAng) && (heading <= 180 - maxAng)) || ((heading >= maxAng - 180) && (heading < -maxAng))) {
		return false;
	}

	if(side == RIGHT_SIDE){
		if (v->x < 0) { // suche neue richtung wenn richtung = alteRichtung oder Richtung.y = 0 oder ball bewegt sich nach rechts
			return false;
		}
	} else if (side == LEFT_SIDE) { // suche neue richtung wenn richtung = alteRichtung oder Richtung.y = 0 oder ball bewegt sich nach links
		if (v->x > 0) {
			return false;
		}
	}

	return true;
}

Vector Puck::newVel(bool side)
{
	Vector newVel = Vector(RANDOM_2D);
	while (!checkVel(&newVel, side)) { 
		newVel = Vector(RANDOM_2D);
	}

	newVel.mult(speed);
	return newVel;
}

Vector Puck::newVel()
{
	Vector newVel = Vector(RANDOM_2D);
	while (!checkVel(&newVel)) {
		newVel = Vector(RANDOM_2D);
	}
	newVel.mult(speed);
	return newVel;
}

Puck puck;