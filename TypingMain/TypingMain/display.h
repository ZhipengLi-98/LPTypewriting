#pragma once

// opencvʵ��
// ��������������һ������һ��
// ���ֽ��ղ���ָ��ڼ��������ֽ���Ҫ��ʾ���ַ�

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
