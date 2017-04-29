
#include "Arduino.h"
#include "Vector.h"

Vector::Vector(){}

Vector::Vector(float _x, float _y)
{
  x = _x;
  y = _y;
}

Vector::Vector(const Vector& v)
{
  x = v.x;
  y = v.y;
}

Vector::Vector(bool random2D)
{
  if(random2D)
  {
    x = random(-100,120);
		if (x > 100)
			x = 100;
    x /= 100;
    y = random(-100,120);
		if(y > 100)
			y = 100;
    y /= 100;
		
    normalize();
  }
}

//Vector::Vector(float angle)
//{
//	x = cos(angle);
//	y = sin(angle);
//}

void Vector::normalize()
{
  float m = mag();
  if (m != 0 && m != 1){
    div(m);
  }
}

void Vector::add(const Vector& v)
{
  x += v.x;
  y += v.y;
}

void Vector::div(float n)
{
  x /= n;
  y /= n; 
}

void Vector::mult(float n)
{
  x *= n;
  y *= n;
}

float Vector::heading()
{
  float angle = atan2(y, x);
  return -1 * angle;
}

float Vector::mag()
{
  float m = sqrt(x*x + y*y);
  return m;
}
