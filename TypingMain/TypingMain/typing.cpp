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
	isword[0] = isword[1] = isword[2] = isword[3] = isword[4] = isword[5] = 0;
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
	// int test[6] = {30, 40, 50, 70, 80, 90};
	// char testc[6] = { 'a','b','c','d','e','f' };
	//char testText[] = { "Hello World" };
	char w[6];
	w[0] = wheelR[0][0]; w[1] = wheelR[1][0];
	w[2] = wheelR[2][0]; w[3] = wheelR[3][0];
	w[4] = wheelR[4][0]; w[5] = wheelR[5][0];
	// drawWheel(center + 1, w, picture, angleR);
	if (wheelL == -1)
	{
		drawWheel(-1, wheelR, picture, angleR);
	}
	else
	{
		drawWheel(center + 1, wheelR, picture, angleR);
	}
	// drawWheel(wheelL, testc, picture, test);
	drawText((char*)text.data(), len, picture);
	//counterEmit++;
	//imshow("drawWheel", picture);	
	//waitKey(1);
}

int Typing::getNxt(int i)
{
	if (i == 0)
		return 1;
	if (i == 1)
		return 5;
	if (i == 5)
		return 2;
	if (i == 2)
		return 3;
	if (i == 3)
		return 4;
	return 0;
}

//todo : change angle
void Typing::getVoc()
{
	//inputChar = 'a';
	cout << "Voc : " << word << endl;
	
	//vocRec = voc.getnextn(inputChar, 6);
	//for (int i = 0; i < vocRec.size(); i++)

	AssociWords rec;
	rec = voc.getnexts(word, 4, 2);

	double sum = 0;
	int i = 0;
	int alp = rec.alphas.size();
	int wod = rec.words.size();
	int fir = rec.firstAlphas.size();

	
	cout << alp << " " << wod << " " << fir << endl;
	/*
	for (auto e : rec.alphas)
	{
		cout << e.first << " " << e.second << endl;
	}
	for (auto e : rec.words)
	{
		cout << e.first << " " << e.second << endl;
	}
	for (auto e : rec.firstAlphas)
	{
		cout << e.first << " " << e.second << endl;
	}
	*/

	if (alp > 0)
	{
		for (auto p : rec.alphas)
		{
			//pair<float, string> p;
			cout << p.second << " : " << p.first << endl;
			wheelR[i] = p.second;
			rate[i] = p.first;
			isword[i] = 0;
			sum += p.first;
			i = getNxt(i);
		}
		int j = i;
		i = 0;
		int init = 40;
		int tmp = 0;
		for (int k = 0; k < alp - 1; k++)
		{
			angleR[i] = init + ((rate[i] / sum) * 
				           (360 - (45 * (6 - alp)) - (init * alp)));
			tmp += angleR[i];
			i = getNxt(i);
		}
		angleR[i] = 360 - (45 * (6 - alp)) - tmp;
		i = getNxt(i);
		for (auto p : rec.words)
		{
			//pair<float, string> p;
			cout << p.second << " : " << p.first << endl;
			wheelR[i] = p.second;
			angleR[i] = 45;
			isword[i] = 1;
			i = getNxt(i);
		}
		for (auto p : rec.firstAlphas)
		{
			//pair<float, string> p;
			cout << p.second << " : " << p.first << endl;
			wheelR[i] = p.second;
			angleR[i] = 45;
			isword[i] = 0;
			i = getNxt(i);
		}
	}
	else
	{
		i = 0;
		for (auto p : rec.words)
		{
			//pair<float, string> p;
			cout << p.second << " : " << p.first << endl;
			wheelR[i] = p.second;
			angleR[i] = 60;
			isword[i] = 1;
			i = getNxt(i);
		}
		for (auto p : rec.firstAlphas)
		{
			//pair<float, string> p;
			cout << p.second << " : " << p.first << endl;
			wheelR[i] = p.second;
			angleR[i] = 60;
			isword[i] = 0;
			i = getNxt(i);
		}
	}

	/*
	for (int i = 0; i < 6; i++)
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
	for (int i = 0; i < 5; i++)
	{
		angleR[i] = init + ((rate[i] / sum) * (360 - 6 * init));
		tmp += angleR[i];
	}
	angleR[5] = 360 - tmp;
	*/
}

//todo : round
void Typing::getLeft(double angle) 
{
	center = (floor((angle / 360) * 26));
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
	/*
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
	}*/
	if (!isword[i])
	{
		inputChar = wheelR[i][0];
		cout << "input : " << inputChar << endl;
		word += inputChar;
		text += inputChar;
		len++;
		getVoc();
		wheelL = -1;
		renewWheel();
	}
	else
	{
		cout << "input : " << wheelR[i] << endl;
		text = text.substr(0, text.length() - word.length());
		word = wheelR[i];
		text = text + word;
		len = text.length();
		getVoc();
		wheelL = -1;
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
	inputChar = '.';
	word = "";
	//getVoc();
	wheelR[0] = wheelR[1] = wheelR[2] = wheelR[3] = wheelR[4] = wheelR[5] = ' ';
	angleR[0] = angleR[1] = angleR[2] = angleR[3] = angleR[4] = angleR[5] = 60;
	isword[0] = isword[1] = isword[2] = isword[3] = isword[4] = isword[5] = 0;
	wheelL = -1;
	renewWheel();
}

void Typing::getSps()
{
	cout << endl;
	cout << "space" << endl;
	char inputChar = '.';
	word = "";
	text += " ";
	len++;
	//getVoc();
	wheelR[0] = wheelR[1] = wheelR[2] = wheelR[3] = wheelR[4] = wheelR[5] = ' ';
	angleR[0] = angleR[1] = angleR[2] = angleR[3] = angleR[4] = angleR[5] = 60;
	isword[0] = isword[1] = isword[2] = isword[3] = isword[4] = isword[5] = 0;
	wheelL = -1;
	renewWheel();
}

void Typing::getEnt()
{
	cout << endl;
	cout << "enter" << endl;
	word = "";
	text = "";
	len = 0;
	char inputChar = '.';
	//getVoc();
	wheelR[0] = wheelR[1] = wheelR[2] = wheelR[3] = wheelR[4] = wheelR[5] = ' ';
	angleR[0] = angleR[1] = angleR[2] = angleR[3] = angleR[4] = angleR[5] = 60;
	isword[0] = isword[1] = isword[2] = isword[3] = isword[4] = isword[5] = 0;
	wheelL = -1;
	renewWheel();
}

Typing::~Typing()
{

}