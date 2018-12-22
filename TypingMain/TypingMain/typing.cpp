#include "typing.h"

using namespace std;
using namespace cv;

Typing::Typing()
{
	text = "";
	word = "";
	len = 0;
	counterEmit = counterSlot = 0;
	cout << "voc init start" << endl;
	voc.init();
	cout << "voc init done" << endl;	
	motion.setPointer(this);
	wheelL = -1;
	wheelR[0] = wheelR[1] = wheelR[2] = wheelR[3] = wheelR[4] = wheelR[5] = ' '; 
	angleR[0] = angleR[1] = angleR[2] = angleR[3] = angleR[4] = angleR[5] = 60;
	picture = Mat(720, 1080, CV_8UC3, Scalar(254, 254, 254));
	renewWheel();
	initshow();
}

void Typing::initshow()
{
	thread show(&Typing::runshow, this);
	show.detach();
}

void Typing::runshow()
{
	while (1)
	{
		imshow("drawWheel", picture);	
		waitKey(1);
	}
}

void Typing::renewWheel()
{
	// picture = Mat(720, 1080, CV_8UC3, Scalar(254, 254, 254));
	//int test[6] = {30, 40, 50, 70, 80, 90};
	//char testText[] = { "Hello World" };
	drawWheel(wheelL, wheelR, picture, angleR);
	drawText((char*)text.data(), len, picture);
	//counterEmit++;
	//imshow("drawWheel", picture);	
	//waitKey(1);
}

//todo : change angle
void Typing::getVoc()
{
	//inputChar = 'a';
	cout << "Voc : " << word << endl;
	
	vocRec = voc.getnextn(inputChar, 6);
	//for (int i = 0; i < vocRec.size(); i++)
	double sum = 0;
	for (int i = 0; i < 5; i++)
	{
		pair<float, char> p;
		p = vocRec[i];
		cout << p.second << " : " << p.first << endl;
		wheelR[i] = p.second;
		rate[i] = p.first;
		sum += p.first;
	}
	int tmp = 0;
	int init = 35;
	for (int i = 0; i < 4; i++)
	{
		angleR[i] = init + ((rate[i] / sum) * (360 - 6 * init));
		tmp += angleR[i];
	}
	angleR[5] = 360 - tmp;
}

//todo : round
void Typing::getLeft(double angle) 
{
	int center = (floor((angle / 360) * 26));
	wheelL = floor(angle / 60);
	cout << endl;
	cout << "choose left center : " << (char)(97 + center) <<  endl;
	for (int i = 0; i < 4; i++)
	{
		wheelR[i] = (char) (97 + ((center + i) % 26));
		angleR[i] = 60;
	}
	for (int i = 4; i < 6; i++)
	{
		wheelR[i] = (char)(97 + ((center - (6 - i) + 26) % 26));
		angleR[i] = 60;
	}
	/*
	if (wheelL == 5)
	{
		wheelR[1] = wheelR[2] = wheelR[3] = wheelR[4] = ' ';
	}
	*/
	renewWheel();
}

void Typing::getRight(double angle)
{
	cout << endl;
	//int i = floor(angle / 60);
	int i = 0;
	for (int ang = 0; i < 6; i++) 
	{
		if ((angle >= ang) && (angle < ang + angleR[i])) break;
		ang += angleR[i];
	}
	inputChar = wheelR[i];
	if (inputChar == ' ')
	{
		//useless
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
		word += inputChar;
		text += inputChar;
		len++;
		getVoc();
		renewWheel();
	}
}

void Typing::getDel()
{
	cout << endl;
	cout << "delete" << endl;
	if (len > 0)
	{
		text.pop_back();
		len--;
		if (word.length() > 0) {
			word.pop_back();
		}
	}
	wheelR[0] = wheelR[1] = wheelR[2] = wheelR[3] = wheelR[4] = wheelR[5] = ' ';
	angleR[0] = angleR[1] = angleR[2] = angleR[3] = angleR[4] = angleR[5] = 60;
	wheelL = -1;
	renewWheel();
}

void Typing::getSps()
{
	cout << endl;
	cout << "space" << endl;
	char inputChar = '.';
	getVoc();
	word = "";
	text += " ";
	len++;
	wheelR[0] = wheelR[1] = wheelR[2] = wheelR[3] = wheelR[4] = wheelR[5] = ' ';
	angleR[0] = angleR[1] = angleR[2] = angleR[3] = angleR[4] = angleR[5] = 60;
	wheelL = -1;
	renewWheel();
}

void Typing::getEnt()
{
	cout << endl;
	cout << "enter" << endl;
	char inputChar = '.';
	getVoc();
	word = "";
	text = "";
	len = 0;
	wheelR[0] = wheelR[1] = wheelR[2] = wheelR[3] = wheelR[4] = wheelR[5] = ' ';
	angleR[0] = angleR[1] = angleR[2] = angleR[3] = angleR[4] = angleR[5] = 60;
	wheelL = -1;
	renewWheel();
}

Typing::~Typing()
{

}