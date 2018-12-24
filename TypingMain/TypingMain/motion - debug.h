#pragma once

#include <cstdio>
#include <iostream>
#include <cmath>

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
	float verticalDistance(Vector);
	float angle(Vector);
	void normalize();
	void print();
	~Vector();

private:

};

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
	const float RADIUS_Z = 30.0f;
	const float RADIUS_SPACE = 50.0f;
	const int TIME_INTERVAL = 30;
	Vector baseCoor;
	int leftPinchHold = 0;
	int rightPinchHold = 0;
	int isPalmFlipped = 0;//ÊÖÕÆÊÇ·ñ·­×ª
	int isLeftEnter = 0;
	int isRightEnter = 0;
	int counter = 0;
	Vector flippedCenterLeft;
	Vector flippedCenterRight;

public:
	Motion();
	~Motion();
	void insertNewFrame(float, float, float, float, float, float, Vector, Vector, Vector, Vector);
	void checkNewCenter();//check if there is a new center
	void checkMovement();
	void checkPinch(Vector, Vector);
	void checkPalmDirection(Vector, Vector, Vector, Vector);
	void resetCounter();
	void resetFlipedCounter();
private:

};