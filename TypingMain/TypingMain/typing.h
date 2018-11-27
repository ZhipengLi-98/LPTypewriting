#pragma once

#include <cstdio>
#include <iostream>
#include <cmath>
#include <opencv2\opencv.hpp>
#include <iostream>
#include <cmath>
#include <nlohmann/json.hpp>
#include <fstream>
#include <string>
#include <queue>
#include "LeapC.h"
#include "motion.h"
#include "voc.h"
#include "display.h"

class Typing
{
public:
	Motion motion;
	Voc voc;

	char wheelR[6];
	int wheelL;
	
	cv::Mat picture;
	std::vector<std::pair<float, char>> vocRec;
	char inputChar;

	double angleLeft;
	double angleRight;

	void renewWheel();
	void getVoc();
	void getLeft(double angle);
	void getRight(double angle);

	Typing();
	~Typing();
};