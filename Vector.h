#ifndef Vector_h
#define Vector_h

#include "Arduino.h"

#define RANDOM_2D 1


class Vector{
  public:
  float x, y;

  Vector();
  Vector(float _x, float _y);
  Vector(const Vector& v);
  Vector(bool random2D);
	//Vector(float angle);

  void normalize();
  
  void add(const Vector& v);
  void div(float n);
  void mult(float n);

  float heading();
  float mag();
  
};

#endif
