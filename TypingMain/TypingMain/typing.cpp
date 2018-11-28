#include "typing.h"

using namespace std;
using namespace cv;

Typing::Typing()
{
	cout << "voc init start" << endl;
	voc.init();
	cout << "voc init done" << endl;	
	motion.setPointer(this);
	wheelL = -1;
	wheelR[0] = wheelR[1] = wheelR[2] = wheelR[3] = wheelR[4] = wheelR[5] = ' '; 
	picture = Mat(720, 1080, CV_8UC3, Scalar(254, 254, 254));
	//Mat pic(720, 1080, CV_8UC3, Scalar(254, 254, 254));
	renewWheel();
}



void Typing::renewWheel()
{
	drawWheel(wheelL, wheelR, picture);
	//imshow("drawWheel", picture);	
	//waitKey(-1);
}

void Typing::getVoc()
{
	//inputChar = 'a';
	cout << "be called" << endl;
	
	vocRec = voc.getnextn(inputChar, 6);
	//for (int i = 0; i < vocRec.size(); i++)
	for (int i = 0; i < 5; i++)
	{
		pair<float, char> p;
		p = vocRec[i];
		cout << p.second << " ";
		wheelR[i] = p.second;
	}
	cout << endl;
	
}

void Typing::getLeft(double angle)
{
	wheelL = floor(angle / 60);
	for (int i = 0; i < 5; i++)
	{
		wheelR[i] = (char) (97 + wheelL * 5 + i);
	}
	if (wheelL == 5)
	{
		wheelR[1] = wheelR[2] = wheelR[3] = wheelR[4] = ' ';
	}
	renewWheel();
}

void Typing::getRight(double angle)
{
	int i = floor(angle / 60);
	inputChar = wheelR[i];
	if (inputChar == ' ')
	{
		cout << "back" << endl;
		inputChar = '.';
		getVoc();
		wheelR[0] = wheelR[1] = wheelR[2] = wheelR[3] = wheelR[4] = wheelR[5] = ' '; 
		wheelL = -1;
		renewWheel();
	}
	else
	{
		cout << "input : " << inputChar << endl;
		getVoc();
		renewWheel();
	}
}

Typing::~Typing()
{

}