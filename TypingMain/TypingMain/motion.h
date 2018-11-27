#pragma once

#include <cstdio>
#include <iostream>
#include <cmath>
//#include "typing.h"

class Vector
{
public:
	float x, y, z;
	Vector();
	Vector(float, float, float);
	void minUpdate(Vector);
	void maxUpdate(Vector);
	float distanceSquare(Vector);
	float plainDistanceSquare(Vector);
	float angle(Vector);
	void normalize();
	void print();

	~Vector();

private:

};

class Typing;

class Motion
{
	Vector left[300];
	Vector right[300];
	Vector centerLeft;
	Vector centerRight;
	int freshCount;
	int currentFrame;
	const int TOTALFRAME = 300;
	const int COUNTLIMIT = 50;
	const int CENTERLIMIT = 50;
	const float MINVAL = -1000.0f;
	const float MAXVAL = 1000.0f;
	const float RADIUS = 100.0f;
	Vector baseCoor;

	Typing * pointerTyping;

public:
	Motion();
	~Motion();
	void insertNewFrame(float, float, float, float, float, float);
	void checkNewCenter();//check if there is a new center
	void checkMovement();
	
	void setPointer(Typing * pointer);

private:

};