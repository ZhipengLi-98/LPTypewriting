#include "display.h"

char alphabet[26] = { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z' };
std::string temp[6];
int angleBuffer[6];
std::vector<char> charBuffer;

void drawWheel(int index, string characters[], cv::Mat& picture, int* angles) {
	int flag = 1;
	if (index == -1)
	{
		flag = 0;
		index = 0;
	}
	index -= 7;
	index %= 26;
	// cout << "drawWheel" << endl;
	// cout << "leftWheel " << index << endl;
	// Mat picture(720, 720, CV_8UC3, Scalar(254, 254, 254));

	int r1 = 200;
	Point center1 = Point(250, 400);
	circle(picture, center1, r1, Scalar(20, 20, 20), 3);
	int r2 = 150;
	circle(picture, center1, r2, Scalar(20, 20, 20), 3);
	int r_coverage1 = ((r1 + r2) >> 1) - 10;

	double angle = PI / 3;
	/*
	for (int i = 0; i < 6; i++) {
		double c_angle = angle * i;
		Point start = Point(center1.x + r1 * sin(c_angle), center1.y + r1 * cos(c_angle));
		Point end = Point(center1.x + r2 * sin(c_angle), center1.y + r2 * cos(c_angle));
		line(picture, start, end, Scalar(20, 20, 20), 2, LINE_8);
	}
	*/
	Size axes = Size(r2, r2);
	for (int i = 0; i < 26; i++) {
		ellipse(picture, center1, axes, 0, (double)i * 360.0 / 26.0 - 180.0 / 26.0, (double)i * 360.0 / 26.0 + 180.0 / 26.0, Scalar(255, 255, 255), -1);
	}
	if (flag) 
	{
		ellipse(picture, center1, axes, 0, (double)index * 360.0 / 26.0 - 30.0, (double)index * 360.0 / 26.0 + 30.0, Scalar(100, 100, 100), -1);
	}

	double tAngle = PI / 13;
	putText(picture, "A", Point(center1.x - 5 + r_coverage1 * sin(tAngle / 2), center1.y + 5 - r_coverage1 * cos(tAngle / 2)), 1.5, 1, Scalar::all(0));
	putText(picture, "B", Point(center1.x - 5 + r_coverage1 * sin(tAngle * 3 / 2), center1.y + 5 - r_coverage1 * cos(tAngle * 3 / 2)), 1.5, 1, Scalar::all(0));
	putText(picture, "C", Point(center1.x - 5 + r_coverage1 * sin(tAngle * 5 / 2), center1.y + 5 - r_coverage1 * cos(tAngle * 5 / 2)), 1.5, 1, Scalar::all(0));
	putText(picture, "D", Point(center1.x - 5 + r_coverage1 * sin(tAngle * 7 / 2), center1.y + 5 - r_coverage1 * cos(tAngle * 7 / 2)), 1.5, 1, Scalar::all(0));
	putText(picture, "E", Point(center1.x - 5 + r_coverage1 * sin(tAngle * 9 / 2), center1.y + 5 - r_coverage1 * cos(tAngle * 9 / 2)), 1.5, 1, Scalar::all(0));
	putText(picture, "F", Point(center1.x - 5 + r_coverage1 * sin(tAngle * 11 / 2), center1.y + 5 - r_coverage1 * cos(tAngle * 11 / 2)), 1.5, 1, Scalar::all(0));
	putText(picture, "G", Point(center1.x - 5 + r_coverage1 * sin(tAngle * 13 / 2), center1.y + 5 - r_coverage1 * cos(tAngle * 13 / 2)), 1.5, 1, Scalar::all(0));
	putText(picture, "H", Point(center1.x - 5 + r_coverage1 * sin(tAngle * 15 / 2), center1.y + 5 - r_coverage1 * cos(tAngle * 15 / 2)), 1.5, 1, Scalar::all(0));
	putText(picture, "I", Point(center1.x - 5 + r_coverage1 * sin(tAngle * 17 / 2), center1.y + 5 - r_coverage1 * cos(tAngle * 17 / 2)), 1.5, 1, Scalar::all(0));
	putText(picture, "J", Point(center1.x - 5 + r_coverage1 * sin(tAngle * 19 / 2), center1.y + 5 - r_coverage1 * cos(tAngle * 19 / 2)), 1.5, 1, Scalar::all(0));
	putText(picture, "K", Point(center1.x - 5 + r_coverage1 * sin(tAngle * 21 / 2), center1.y + 5 - r_coverage1 * cos(tAngle * 21 / 2)), 1.5, 1, Scalar::all(0));
	putText(picture, "L", Point(center1.x - 5 + r_coverage1 * sin(tAngle * 23 / 2), center1.y + 5 - r_coverage1 * cos(tAngle * 23 / 2)), 1.5, 1, Scalar::all(0));
	putText(picture, "M", Point(center1.x - 5 + r_coverage1 * sin(tAngle * 25 / 2), center1.y + 5 - r_coverage1 * cos(tAngle * 25 / 2)), 1.5, 1, Scalar::all(0));
	putText(picture, "N", Point(center1.x - 5 + r_coverage1 * sin(tAngle * 27 / 2), center1.y + 5 - r_coverage1 * cos(tAngle * 27 / 2)), 1.5, 1, Scalar::all(0));
	putText(picture, "O", Point(center1.x - 5 + r_coverage1 * sin(tAngle * 29 / 2), center1.y + 5 - r_coverage1 * cos(tAngle * 29 / 2)), 1.5, 1, Scalar::all(0));
	putText(picture, "P", Point(center1.x - 5 + r_coverage1 * sin(tAngle * 31 / 2), center1.y + 5 - r_coverage1 * cos(tAngle * 31 / 2)), 1.5, 1, Scalar::all(0));
	putText(picture, "Q", Point(center1.x - 5 + r_coverage1 * sin(tAngle * 33 / 2), center1.y + 5 - r_coverage1 * cos(tAngle * 33 / 2)), 1.5, 1, Scalar::all(0));
	putText(picture, "R", Point(center1.x - 5 + r_coverage1 * sin(tAngle * 35 / 2), center1.y + 5 - r_coverage1 * cos(tAngle * 35 / 2)), 1.5, 1, Scalar::all(0));
	putText(picture, "S", Point(center1.x - 5 + r_coverage1 * sin(tAngle * 37 / 2), center1.y + 5 - r_coverage1 * cos(tAngle * 37 / 2)), 1.5, 1, Scalar::all(0));
	putText(picture, "T", Point(center1.x - 5 + r_coverage1 * sin(tAngle * 39 / 2), center1.y + 5 - r_coverage1 * cos(tAngle * 39 / 2)), 1.5, 1, Scalar::all(0));
	putText(picture, "U", Point(center1.x - 5 + r_coverage1 * sin(tAngle * 41 / 2), center1.y + 5 - r_coverage1 * cos(tAngle * 41 / 2)), 1.5, 1, Scalar::all(0));
	putText(picture, "V", Point(center1.x - 5 + r_coverage1 * sin(tAngle * 43 / 2), center1.y + 5 - r_coverage1 * cos(tAngle * 43 / 2)), 1.5, 1, Scalar::all(0));
	putText(picture, "W", Point(center1.x - 5 + r_coverage1 * sin(tAngle * 45 / 2), center1.y + 5 - r_coverage1 * cos(tAngle * 45 / 2)), 1.5, 1, Scalar::all(0));
	putText(picture, "X", Point(center1.x - 5 + r_coverage1 * sin(tAngle * 47 / 2), center1.y + 5 - r_coverage1 * cos(tAngle * 47 / 2)), 1.5, 1, Scalar::all(0));
	putText(picture, "Y", Point(center1.x - 5 + r_coverage1 * sin(tAngle * 49 / 2), center1.y + 5 - r_coverage1 * cos(tAngle * 49 / 2)), 1.5, 1, Scalar::all(0));
	putText(picture, "Z", Point(center1.x - 5 + r_coverage1 * sin(tAngle * 51 / 2), center1.y + 5 - r_coverage1 * cos(tAngle * 51 / 2)), 1.5, 1, Scalar::all(0));

	// cout << "rightWheel" << endl;
	// Mat picture(720, 720, CV_8UC3, Scalar(254, 254, 254));

	int r3 = 200;
	Point center2 = Point(750, 400);
	circle(picture, center2, r1, Scalar(20, 20, 20), 3);
	int r4 = 150;
	// circle(picture, center2, r2, Scalar(20, 20, 20), 3);
	// int r_coverage2 = ((r1 + r2) >> 1) - 10;
	int r_coverage2 = r2;

	for (int i = 0; i < 6; i++) {
		int t = 0;
		for (int j = 0; j < i; j++) {
			t += angleBuffer[j];
		}
		double c_angle = (double)t / 360 * 2 * PI;
		Point start = Point(center2.x + r1 * sin(c_angle), center2.y - r1 * cos(c_angle));
		Point end = Point(center2.x + r2 * sin(c_angle), center2.y - r2 * cos(c_angle));
		// line(picture, start, end, Scalar::all(255), 2, LINE_8);
		line(picture, start, center2, Scalar::all(255), 2, LINE_8);
	}
	circle(picture, center2, r1, Scalar(20, 20, 20), 3);
	// circle(picture, center2, r2, Scalar(20, 20, 20), 3);

	// cv::String string = ((const char*)characters);
	// cv::String(characters);

	for (int i = 0; i < 6; i++) {
		int t = 0;
		for (int j = 0; j < i; j++) {
			t += angleBuffer[j];
		}
		t += angleBuffer[i] / 2;
		double tempAngle = (double)t / 360 * 2 * PI;
		putText(picture, cv::String(temp[i]), Point(center2.x - 10 + r_coverage2 * sin(tempAngle), center2.y - r_coverage2 * cos(tempAngle)), 1.5, 1.5, Scalar::all(255));
	}

	/*
	putText(picture, cv::String(sizeof(char), temp[0]), Point(center2.x - 10 + r_coverage2 * sin(angle / 2), center2.y - r_coverage2 * cos(angle / 2)), 1.5, 1, Scalar::all(255));
	putText(picture, cv::String(sizeof(char), temp[1]), Point(center2.x - 10 + r_coverage2 * sin(angle * 3 / 2), center2.y - r_coverage2 * cos(angle * 3 / 2)), 1.5, 1, Scalar::all(255));
	putText(picture, cv::String(sizeof(char), temp[2]), Point(center2.x - 10 + r_coverage2 * sin(angle * 5 / 2), center2.y - r_coverage2 * cos(angle * 5 / 2)), 1.5, 1, Scalar::all(255));
	putText(picture, cv::String(sizeof(char), temp[3]), Point(center2.x - 10 + r_coverage2 * sin(angle * 7 / 2), center2.y - r_coverage2 * cos(angle * 7 / 2)), 1.5, 1, Scalar::all(255));
	putText(picture, cv::String(sizeof(char), temp[4]), Point(center2.x - 10 + r_coverage2 * sin(angle * 9 / 2), center2.y - r_coverage2 * cos(angle * 9 / 2)), 1.5, 1, Scalar::all(255));
	putText(picture, cv::String(sizeof(char), temp[5]), Point(center2.x - 10 + r_coverage2 * sin(angle * 11 / 2), center2.y - r_coverage2 * cos(angle * 11 / 2)), 1.5, 1, Scalar::all(255));
	*/

	for (int i = 0; i < 6; i++) {
		// double c_angle = angle * i;
		angleBuffer[i] = angles[i];
		int t = 0;
		for (int j = 0; j < i; j++) {
			t += angles[j];
		}
		double c_angle = (double)t / 360 * 2 * PI;
		//std::cout << c_angle << std::endl;
		Point start = Point(center2.x + r1 * sin(c_angle), center2.y - r1 * cos(c_angle));
		Point end = Point(center2.x + r2 * sin(c_angle), center2.y - r2 * cos(c_angle));
		// line(picture, start, end, Scalar::all(0), 2, LINE_8);
		line(picture, start, center2, Scalar::all(0), 2, LINE_8);
	}

	// Size axes = Size(r2, r2);
	// ellipse(picture, center, axes, 0, index * 60 - 30, index * 60 + 30, Scalar(100, 100, 100), -1);

	for (int i = 0; i < 6; i++) {
		temp[i] = characters[i];
		double t = 0;
		for (int j = 0; j < i; j++) {
			t += angleBuffer[j];
		}
		t += angleBuffer[i] / 2;
		double tempAngle = (double)t / 360 * 2 * PI;
		putText(picture, cv::String(characters[i]), Point(center2.x - 10 + r_coverage2 * sin(tempAngle), center2.y - r_coverage2 * cos(tempAngle)), 1.5, 1.5, Scalar::all(0));
	}

	/*
	putText(picture, cv::String(sizeof(char), characters[0]), Point(center2.x - 10 + r_coverage2 * sin(angle / 2), center2.y - r_coverage2 * cos(angle / 2)), 1.5, 1, Scalar::all(0));
	putText(picture, cv::String(sizeof(char), characters[1]), Point(center2.x - 10 + r_coverage2 * sin(angle * 3 / 2), center2.y - r_coverage2 * cos(angle * 3 / 2)), 1.5, 1, Scalar::all(0));
	putText(picture, cv::String(sizeof(char), characters[2]), Point(center2.x - 10 + r_coverage2 * sin(angle * 5 / 2), center2.y - r_coverage2 * cos(angle * 5 / 2)), 1.5, 1, Scalar::all(0));
	putText(picture, cv::String(sizeof(char), characters[3]), Point(center2.x - 10 + r_coverage2 * sin(angle * 7 / 2), center2.y - r_coverage2 * cos(angle * 7 / 2)), 1.5, 1, Scalar::all(0));
	putText(picture, cv::String(sizeof(char), characters[4]), Point(center2.x - 10 + r_coverage2 * sin(angle * 9 / 2), center2.y - r_coverage2 * cos(angle * 9 / 2)), 1.5, 1, Scalar::all(0));
	putText(picture, cv::String(sizeof(char), characters[5]), Point(center2.x - 10 + r_coverage2 * sin(angle * 11 / 2), center2.y - r_coverage2 * cos(angle * 11 / 2)), 1.5, 1, Scalar::all(0));
	*/

	// imshow("rightWheel", picture);
	// waitKey(-1);

	// imshow("leftWheel", picture);
	// waitKey(-1);
}

void drawText(char* text, int len, cv::Mat& picture) {
	int rows = 0;
	int width = 0;
	for (int i = 0; i < charBuffer.size(); i++) {
		width++;
		if (width > 29) {
			width -= 30;
			rows++;
		}
		putText(picture, cv::String(sizeof(char), charBuffer[i]), Point(200 + width * 20, 50 + rows * 20), 1.5, 2, Scalar::all(255));
	}
	
	rows = 0;
	width = 0;
	charBuffer.clear();
	for (int i = 0; i < len; i++) {
		width++;
		charBuffer.push_back(text[i]);
		if (width > 29) {
			width -= 30;
			rows++;
		}
		putText(picture, cv::String(sizeof(char), text[i]), Point(200 + width * 20, 50 + rows * 20), 1.5, 2, Scalar::all(0));
	}
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

	cv::String string = ((const char*)characters);
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