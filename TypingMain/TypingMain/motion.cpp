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

float Vector::verticalDistance(Vector v)
{
	return y - v.y;
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
	leftPinchHold = 0;
	rightPinchHold = 0;
	isPalmFlipped = 0;
	flippedCenterLeft = Vector(0, 0, 0);
	flippedCenterRight = Vector(0, 0, 0);
	isLeftEnter = 0;
	isRightEnter = 0;
}

void Motion::setPointer(Typing * pointer)
{
	pointerTyping = pointer;
	//pointerTyping -> getVoc();
}

Motion::~Motion()
{
}

void Motion::insertNewFrame(float lx, float ly, float lz, float rx, float ry, float rz, Vector leftPinch, Vector rightPinch, Vector leftPalmDirection, Vector rightPalmDirection)
{
	currentFrame++;
	currentFrame %= TOTALFRAME;//keep in array limit
	left[currentFrame] = Vector(lx, ly, lz);
	right[currentFrame] = Vector(rx, ry, rz);
	freshCount++;
	checkPalmDirection(leftPalmDirection, rightPalmDirection, left[currentFrame], right[currentFrame]);
	checkPinch(leftPinch, rightPinch);
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

void Motion::checkMovement()//检测手是否移出阈值，是则调用触发动作函数
{
	Vector leftNew = left[currentFrame];
	Vector rightNew = right[currentFrame];
	Vector leftOld = left[(currentFrame - 1) % TOTALFRAME];
	Vector rightOld = right[(currentFrame - 1) % TOTALFRAME];
	if (isPalmFlipped == 0) {//normal gestures detection
		if (leftOld.plainDistanceSquare(centerLeft) < RADIUS*RADIUS && leftNew.plainDistanceSquare(centerLeft) > RADIUS*RADIUS && centerLeft.distanceSquare(Vector(0, 0, 0)) > 1e-6) {
			if (leftPinchHold == 1) {
				pointerTyping->getDel();
				//printf("left delete\n");
			}
			else
			{
				Vector v;
				v.x = leftNew.x - centerLeft.x;
				v.y = 0;
				v.z = leftNew.z - centerLeft.z;
				v.normalize();
				pointerTyping->getLeft(baseCoor.angle(v));
				printf("left movement: angle = %f\n", baseCoor.angle(v));
			}
		}
		if (rightOld.plainDistanceSquare(centerRight) < RADIUS*RADIUS && rightNew.plainDistanceSquare(centerRight) > RADIUS*RADIUS && centerRight.distanceSquare(Vector(0, 0, 0)) > 1e-6) {
			if (rightPinchHold == 1) {
				pointerTyping->getDel();
				//printf("right delete\n");
			}
			else {
				Vector v;
				v.x = rightNew.x - centerRight.x;
				v.y = 0;
				v.z = rightNew.z - centerRight.z;
				v.normalize();
				pointerTyping->getRight(baseCoor.angle(v));
				printf("right movement: angle = %f\n", baseCoor.angle(v));
			}
		}
		if (leftOld.verticalDistance(centerLeft) > (-1)*RADIUS_Z && leftNew.verticalDistance(centerLeft) < (-1)*RADIUS_Z && centerLeft.distanceSquare(Vector(0, 0, 0)) > 1e-6) {
			pointerTyping->getSps();
			//printf("left space\n");
		}
		if (rightOld.verticalDistance(centerRight) > (-1)*RADIUS_Z && rightNew.verticalDistance(centerRight) < (-1)*RADIUS_Z && centerRight.distanceSquare(Vector(0, 0, 0)) > 1e-6) {
			pointerTyping->getSps();
			//printf("right space\n");
		}
	}
	else {//fliped gestures detection: ENTER
		if (leftOld.verticalDistance(flippedCenterLeft) < RADIUS_Z && leftNew.verticalDistance(flippedCenterLeft) > RADIUS_Z && flippedCenterLeft.distanceSquare(Vector(0, 0, 0)) > 1e-6) {
			//printf("left enter: ");
			leftNew.print();
			isLeftEnter = 1;
		}
		if (rightOld.verticalDistance(flippedCenterRight) < RADIUS_Z && rightNew.verticalDistance(flippedCenterRight) > RADIUS_Z && flippedCenterRight.distanceSquare(Vector(0, 0, 0)) > 1e-6) {
			//printf("right enter: ");
			rightNew.print();
			isRightEnter = 1;
		}
		if (isLeftEnter == 1 && isRightEnter == 1) {
			pointerTyping->getEnt();
			//printf("both enter\n");
			isLeftEnter = 0;
			isRightEnter = 0;
		}
	}
}

void Motion::checkPinch(Vector leftPinch, Vector rightPinch)
{
	leftPinchHold = (abs(leftPinch.x - 1.0f) < 0.05f && leftPinch.y < 20.0f) ? 1 : 0;
	rightPinchHold = (abs(rightPinch.x - 1.0f) < 0.05f && rightPinch.y < 20.0f) ? 1 : 0;
	//printf("leftPinch: %d, rightPinch: %d\n", leftPinchHold, rightPinchHold);
}

void Motion::checkPalmDirection(Vector leftPalmDirection, Vector rightPalmDirection, Vector left, Vector right)
{	
	if (abs(leftPalmDirection.y - 1.0f) < 0.1f && abs(rightPalmDirection.y - 1.0f) < 0.1f) {
		if (isPalmFlipped == 0) {
			isPalmFlipped = 1;
			//printf("flipped\n");
			//record fliped coordinate
			flippedCenterLeft = left;
			flippedCenterRight = right;
			isLeftEnter = 0;
			isRightEnter = 0;
			//printf("flippedcenterleft: ");
			flippedCenterLeft.print();
			//printf("flippedcenterright: ");
			flippedCenterRight.print();
		}
	}
	else if(abs(leftPalmDirection.y + 1.0f) < 0.1f && abs(rightPalmDirection.y + 1.0f) < 0.1f){
		if (isPalmFlipped == 1) {
			//printf("flipped back\n");
			isPalmFlipped = 0;
			isLeftEnter = 0;
			isRightEnter = 0;
			centerLeft = left;
			centerRight = right;
			//printf("centerleft: ");
			centerLeft.print();
			//printf("centerright: ");
			centerRight.print();
		}
	}
}
