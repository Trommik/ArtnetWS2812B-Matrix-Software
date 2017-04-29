// Puck.h

#ifndef _PUCK_h
#define _PUCK_h

#include "PongGame.h"
#include "Vector.h"

class Puck
{
 public:

	Vector pos;
  Vector vel;

	void init();
	//void init(float speed, int maxAng, Vector vel);

	void update();

	renderData render();
	renderData renderLast();
	renderData renderLastLast();

 private:
	 renderData puckRenderData[3] = {{8,8,PUCK}, {8,8,PUCK}, {8,8,PUCK}};

	float speed;
	int maxAng;

	void edges();

	//Vector newVel(bool side);
	Vector newVel(bool side);
	Vector newVel();

	bool checkVel(Vector *v);
	bool checkVel(Vector *v, bool side);
};

extern Puck puck;

#include "Paddel.h"

#endif

