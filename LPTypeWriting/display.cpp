#include "display.h"

char alphabet[26] = { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z' };

void drawWheel(int index, char* characters, cv::Mat& picture) {
	index -= 1;
	index %= 6;
	cout << "drawWheel" << endl;
	// cout << "leftWheel " << index << endl;
	// Mat picture(720, 720, CV_8UC3, Scalar(254, 254, 254));

	int r1 = 200;
	Point center1 = Point(250, 400);
	circle(picture, center1, r1, Scalar(20, 20, 20), 3);
	int r2 = 150;
	circle(picture, center1, r2, Scalar(20, 20, 20), 3);
	int r_coverage1 = ((r1 + r2) >> 1) - 10;

	double angle = PI / 3;
	for (int i = 0; i < 6; i++) {
		double c_angle = angle * i;
		Point start = Point(center1.x + r1 * sin(c_angle), center1.y + r1 * cos(c_angle));
		Point end = Point(center1.x + r2 * sin(c_angle), center1.y + r2 * cos(c_angle));
		line(picture, start, end, Scalar(20, 20, 20), 2, LINE_8);
	}
	Size axes = Size(r2, r2);
	ellipse(picture, center1, axes, 0, index * 60 - 30, index * 60 + 30, Scalar(100, 100, 100), -1);

	putText(picture, "A-E", Point(center1.x - 10 + r_coverage1 * sin(angle / 2), center1.y - r_coverage1 * cos(angle / 2)), 1.5, 1, Scalar::all(0));
	putText(picture, "E-I", Point(center1.x - 10 + r_coverage1 * sin(angle * 3 / 2), center1.y - r_coverage1 * cos(angle * 3 / 2)), 1.5, 1, Scalar::all(0));
	putText(picture, "I-M", Point(center1.x - 10 + r_coverage1 * sin(angle * 5 / 2), center1.y - r_coverage1 * cos(angle * 5 / 2)), 1.5, 1, Scalar::all(0));
	putText(picture, "M-Q", Point(center1.x - 10 + r_coverage1 * sin(angle * 7 / 2), center1.y - r_coverage1 * cos(angle * 7 / 2)), 1.5, 1, Scalar::all(0));
	putText(picture, "Q-U", Point(center1.x - 10 + r_coverage1 * sin(angle * 9 / 2), center1.y - r_coverage1 * cos(angle * 9 / 2)), 1.5, 1, Scalar::all(0));
	putText(picture, "U-Z", Point(center1.x - 10 + r_coverage1 * sin(angle * 11 / 2), center1.y - r_coverage1 * cos(angle * 11 / 2)), 1.5, 1, Scalar::all(0));

	// cout << "rightWheel" << endl;
	// Mat picture(720, 720, CV_8UC3, Scalar(254, 254, 254));
	
	int r3 = 200;
	Point center2 = Point(750, 400);
	circle(picture, center2, r1, Scalar(20, 20, 20), 3);
	int r4 = 150;
	circle(picture, center2, r2, Scalar(20, 20, 20), 3);
	int r_coverage2 = ((r1 + r2) >> 1) - 10;

	for (int i = 0; i < 6; i++) {
		double c_angle = angle * i;
		Point start = Point(center2.x + r1 * sin(c_angle), center2.y + r1 * cos(c_angle));
		Point end = Point(center2.x + r2 * sin(c_angle), center2.y + r2 * cos(c_angle));
		line(picture, start, end, Scalar(20, 20, 20), 2, LINE_8);
	}
	
	// Size axes = Size(r2, r2);
	// ellipse(picture, center, axes, 0, index * 60 - 30, index * 60 + 30, Scalar(100, 100, 100), -1);

	cv::String string = ((const char*)characters);
	cv::String(sizeof(char), characters[0]);

	putText(picture, cv::String(sizeof(char), characters[0]), Point(center2.x - 10 + r_coverage2 * sin(angle / 2), center2.y - r_coverage2 * cos(angle / 2)), 1.5, 1, Scalar::all(0));
	putText(picture, cv::String(sizeof(char), characters[1]), Point(center2.x - 10 + r_coverage2 * sin(angle * 3 / 2), center2.y - r_coverage2 * cos(angle * 3 / 2)), 1.5, 1, Scalar::all(0));
	putText(picture, cv::String(sizeof(char), characters[2]), Point(center2.x - 10 + r_coverage2 * sin(angle * 5 / 2), center2.y - r_coverage2 * cos(angle * 5 / 2)), 1.5, 1, Scalar::all(0));
	putText(picture, cv::String(sizeof(char), characters[3]), Point(center2.x - 10 + r_coverage2 * sin(angle * 7 / 2), center2.y - r_coverage2 * cos(angle * 7 / 2)), 1.5, 1, Scalar::all(0));
	putText(picture, cv::String(sizeof(char), characters[4]), Point(center2.x - 10 + r_coverage2 * sin(angle * 9 / 2), center2.y - r_coverage2 * cos(angle * 9 / 2)), 1.5, 1, Scalar::all(0));
	putText(picture, cv::String(sizeof(char), characters[5]), Point(center2.x - 10 + r_coverage2 * sin(angle * 11 / 2), center2.y - r_coverage2 * cos(angle * 11 / 2)), 1.5, 1, Scalar::all(0));

	// imshow("rightWheel", picture);
	// waitKey(-1);

	// imshow("leftWheel", picture);
	// waitKey(-1);
}

// useless
void leftWheel(int index) {
	index -= 1;
	index %= 6;
	// cout << "leftWheel " << index << endl;
	Mat picture(720, 720, CV_8UC3, Scalar(254, 254, 254));

	int r1 = 200;
	Point center = Point(250, 400);
	circle(picture, center, r1, Scalar(20, 20, 20), 3);
	int r2 = 150;
	circle(picture, center, r2, Scalar(20, 20, 20), 3);
	int r_coverage = ((r1 + r2) >> 1) - 10;

	double angle = PI / 3;
	for (int i = 0; i < 6; i++) {
		double c_angle = angle * i;
		Point start = Point(center.x + r1 * sin(c_angle), center.y + r1 * cos(c_angle));
		Point end = Point(center.x + r2 * sin(c_angle), center.y + r2 * cos(c_angle));
		line(picture, start, end, Scalar(20, 20, 20), 2, LINE_8);
	}
	Size axes = Size(r2, r2);
	ellipse(picture, center, axes, 0, index * 60 - 30, index * 60 + 30, Scalar(100, 100, 100), -1);

	putText(picture, "A-E", Point(center.x - 10 + r_coverage * sin(angle / 2), center.y - r_coverage * cos(angle / 2)), 1.5, 1, Scalar::all(0));
	putText(picture, "E-I", Point(center.x - 10 + r_coverage * sin(angle * 3 / 2), center.y - r_coverage * cos(angle * 3 / 2)), 1.5, 1, Scalar::all(0));
	putText(picture, "I-M", Point(center.x - 10 + r_coverage * sin(angle * 5 / 2), center.y - r_coverage * cos(angle * 5 / 2)), 1.5, 1, Scalar::all(0));
	putText(picture, "M-Q", Point(center.x - 10 + r_coverage * sin(angle * 7 / 2), center.y - r_coverage * cos(angle * 7 / 2)), 1.5, 1, Scalar::all(0));
	putText(picture, "Q-U", Point(center.x - 10 + r_coverage * sin(angle * 9 / 2), center.y - r_coverage * cos(angle * 9 / 2)), 1.5, 1, Scalar::all(0));
	putText(picture, "U-Z", Point(center.x - 10 + r_coverage * sin(angle * 11 / 2), center.y - r_coverage * cos(angle * 11 / 2)), 1.5, 1, Scalar::all(0));

	imshow("leftWheel", picture);
	waitKey(-1);
}

// useless
void rightWheel(char* characters) {
	cout << "rightWheel" << endl;
	Mat picture(720, 720, CV_8UC3, Scalar(254, 254, 254));

	int r1 = 200;
	Point center = Point(250, 400);
	circle(picture, center, r1, Scalar(20, 20, 20), 3);
	int r2 = 150;
	circle(picture, center, r2, Scalar(20, 20, 20), 3);
	int r_coverage = ((r1 + r2) >> 1) - 10;

	double angle = PI / 3;
	for (int i = 0; i < 6; i++) {
		double c_angle = angle * i;
		Point start = Point(center.x + r1 * sin(c_angle), center.y + r1 * cos(c_angle));
		Point end = Point(center.x + r2 * sin(c_angle), center.y + r2 * cos(c_angle));
		line(picture, start, end, Scalar(20, 20, 20), 2, LINE_8);
	}
	// Size axes = Size(r2, r2);
	// ellipse(picture, center, axes, 0, index * 60 - 30, index * 60 + 30, Scalar(100, 100, 100), -1);

	cv::String string = ((const char*) characters);
	cv::String(sizeof(char), characters[0]);

	putText(picture, cv::String(sizeof(char), characters[0]), Point(center.x - 10 + r_coverage * sin(angle / 2), center.y - r_coverage * cos(angle / 2)), 1.5, 1, Scalar::all(0));
	putText(picture, cv::String(sizeof(char), characters[1]), Point(center.x - 10 + r_coverage * sin(angle * 3 / 2), center.y - r_coverage * cos(angle * 3 / 2)), 1.5, 1, Scalar::all(0));
	putText(picture, cv::String(sizeof(char), characters[2]), Point(center.x - 10 + r_coverage * sin(angle * 5 / 2), center.y - r_coverage * cos(angle * 5 / 2)), 1.5, 1, Scalar::all(0));
	putText(picture, cv::String(sizeof(char), characters[3]), Point(center.x - 10 + r_coverage * sin(angle * 7 / 2), center.y - r_coverage * cos(angle * 7 / 2)), 1.5, 1, Scalar::all(0));
	putText(picture, cv::String(sizeof(char), characters[4]), Point(center.x - 10 + r_coverage * sin(angle * 9 / 2), center.y - r_coverage * cos(angle * 9 / 2)), 1.5, 1, Scalar::all(0));
	putText(picture, cv::String(sizeof(char), characters[5]), Point(center.x - 10 + r_coverage * sin(angle * 11 / 2), center.y - r_coverage * cos(angle * 11 / 2)), 1.5, 1, Scalar::all(0));

	imshow("rightWheel", picture);
	waitKey(-1);
}