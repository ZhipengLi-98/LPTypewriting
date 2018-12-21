#pragma once

// opencv实现
// 两个函数，左手一个右手一个
// 左手接收参数指向第几个，右手接收要显示的字符

#include <opencv2\opencv.hpp>
#include <iostream>
#include <cmath>

using namespace cv;
using namespace std;

#define PI 3.1415926

void drawWheel(int index, char* characters, cv::Mat& picture, int* angles);

void drawText(char* text, int len, cv::Mat& picture);

// useless
void leftWheel(int index);

// useless
void rightWheel(char* characters);
