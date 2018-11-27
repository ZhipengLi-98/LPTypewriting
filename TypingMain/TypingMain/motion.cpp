#include "motion.h"

#include "typing.h"

#define PI 3.14159265

Vector::Vector(float _x, float _y, float _z)
{
	x = _x;
	y = _y;
	z = _z;
}

void Vector::minUpdate(Vector v)
{
	if (x > v.x) x = v.x;
	if (y > v.y) y = v.y;
	if (z > v.z) z = v.z;
}

void Vector::maxUpdate(Vector v)
{
	if (x < v.x) x = v.x;
	if (y < v.y) y = v.y;
	if (z < v.z) z = v.z;
}

float Vector::distanceSquare(Vector v)
{
	return (x - v.x)*(x - v.x) + (y - v.y)*(y - v.y) + (z - v.z)*(z - v.z);
}

float Vector::plainDistanceSquare(Vector v)
{
	return (x - v.x)*(x - v.x) + (z - v.z)*(z - v.z);
}

float Vector::angle(Vector v)
{
	if(v.x > 0)
		return acos(v.x*x + v.z*z) * 180.0 / PI;
	else
		return 360 - acos(v.x*x + v.z*z) * 180.0 / PI;
}

void Vector::normalize()
{
	float length = sqrt(x*x + y*y + z*z);
	if (length > 1e-6) {
		x /= length;
		y /= length;
		z /= length;
	}
}

void Vector::print()
{
	printf("%.3f %.3f %.3f\n", x, y, z);
}

Vector::Vector()
{
	x = 0;
	y = 0;
	z = 0;
}

Vector::~Vector()
{
}

Motion::Motion()
{
	pointerTyping = NULL;

	freshCount = 0;
	currentFrame = -1;
	centerLeft = Vector(0, 0, 0);
	centerRight = Vector(0, 0, 0);
	baseCoor.x = 0.0f;
	baseCoor.y = 0.0f;
	baseCoor.z = -1.0f;
}

void Motion::setPointer(Typing * pointer)
{
	pointerTyping = pointer;
	//pointerTyping -> getVoc();
}

Motion::~Motion()
{
}

void Motion::insertNewFrame(float lx, float ly, float lz, float rx, float ry, float rz)
{
	currentFrame++;
	currentFrame %= TOTALFRAME;//keep in array limit
	left[currentFrame] = Vector(lx, ly, lz);
	right[currentFrame] = Vector(rx, ry, rz);
	freshCount++;
	checkMovement();
	if (freshCount == COUNTLIMIT) {
		freshCount = 0;
		checkNewCenter();
	}
}

void Motion::checkNewCenter()//如果连续CENTERLIMIT个点都在阈值内，那么就更新手掌中心点。
{
	//left hand
	Vector vecMax(MINVAL, MINVAL, MINVAL);
	Vector vecMin(MAXVAL, MAXVAL, MAXVAL);
	for (int i = currentFrame; i > currentFrame - CENTERLIMIT; --i) {
		vecMax.maxUpdate(left[i%TOTALFRAME]);
		vecMin.minUpdate(left[i%TOTALFRAME]);
	}
	if (vecMax.distanceSquare(vecMin) < 500) {//new center left
		centerLeft.x = (vecMax.x + vecMin.x) / 2;
		centerLeft.y = (vecMax.y + vecMin.y) / 2;
		centerLeft.z = (vecMax.z + vecMin.z) / 2;
	}
	//printf("left hand center: ");
	//centerLeft.print();
	//right hand
	vecMax = Vector(MINVAL, MINVAL, MINVAL);
	vecMin = Vector(MAXVAL, MAXVAL, MAXVAL);
	for (int i = currentFrame; i > currentFrame - CENTERLIMIT; --i) {
		vecMax.maxUpdate(right[i%TOTALFRAME]);
		vecMin.minUpdate(right[i%TOTALFRAME]);
	}
	if (vecMax.distanceSquare(vecMin) < 500) {//new center right
		centerRight.x = (vecMax.x + vecMin.x) / 2;
		centerRight.y = (vecMax.y + vecMin.y) / 2;
		centerRight.z = (vecMax.z + vecMin.z) / 2;
	}
	//printf("right hand center: ");
	//centerRight.print();
}

void Motion::checkMovement()
{
	Vector leftNew = left[currentFrame];
	Vector rightNew = right[currentFrame];
	Vector leftOld = left[(currentFrame - 1) % TOTALFRAME];
	Vector rightOld = right[(currentFrame - 1) % TOTALFRAME];
	if (leftOld.plainDistanceSquare(centerLeft) < RADIUS*RADIUS && leftNew.plainDistanceSquare(centerLeft) > RADIUS*RADIUS && centerLeft.distanceSquare(Vector(0,0,0)) > 1e-6) {
		Vector v;
		v.x = leftNew.x - centerLeft.x;
		v.y = 0;
		v.z = leftNew.z - centerLeft.z;
		v.normalize();
		//pointerTyping -> getVoc();
		pointerTyping -> getLeft(baseCoor.angle(v));
		printf("left movement: angle = %f\n", baseCoor.angle(v));
	}
	if (rightOld.plainDistanceSquare(centerRight) < RADIUS*RADIUS && rightNew.plainDistanceSquare(centerRight) > RADIUS*RADIUS && centerRight.distanceSquare(Vector(0, 0, 0)) > 1e-6) {
		Vector v;
		v.x = rightNew.x - centerRight.x;
		v.y = 0;
		v.z = rightNew.z - centerRight.z;
		v.normalize();
		//pointerTyping -> getVoc();
		pointerTyping -> getRight(baseCoor.angle(v));
		printf("right movement: angle = %f\n", baseCoor.angle(v));
	}
}


