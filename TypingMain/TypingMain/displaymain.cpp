#include "LeapC.h"

#include <iostream>

#include "display.h"

int maindisplay() {
	char test[] = { 'a', 'b', 'c', 'd', 'e', 'f'};
	Mat picture(720, 1080, CV_8UC3, Scalar(254, 254, 254));
	drawWheel(0, test, picture);
	imshow("drawWheel", picture);
	waitKey(-1);
	// system("pause");
	return 0;
}