// voc.cpp: 定义控制台应用程序的入口点。
//
//#include "stdafx.h"
#include "voc.h"

using json = nlohmann::json;
using namespace std;



//Voc voc;

int Voc::getFreq(string prefix)
{
	if (prefix == "") return getAllFreq();
	if (data.count(prefix) == 0) return 0;
	return data[prefix];	
}

int Voc::getAllFreq()
{
	return allfreq ? allfreq : 1;
}

void Voc::clearall()
{
	data = NULL;
	allfreq = 0;
	prefix = "";	
}

void Voc::clearprefix()
{
	prefix = "";
}

void Voc::init()
{
	clearall();
	ifstream i(datapath);
	i >> data;
	for (char i = 'a'; i <= 'z'; i++)
	{
		this->allfreq += getFreq("" + i);
	}	
}

void Voc::debug(string prefix, int num)
{
	for (auto e : getnextn(prefix, num))
	{
		cout << e.first << " " << e.second << endl;
	}
}

void Voc::debug(char c, int num)
{
	for (auto e : getnextn(c, num))
	{
		cout << e.first << " " << e.second << endl;
	}
	cout << "now the accPrefix is " << this->prefix << endl;	
}

const vector<pair<float, char> > Voc::getnextn(string prefix, int num)
{
	priority_queue<pair<float, char> > queue;
	for (char i = 'a'; i <= 'z'; i++)
	{
		float rfreq = float(getFreq(prefix + i) + 1) / (getFreq(prefix) + 26);
		queue.push(make_pair(rfreq, i));
	}
	vector<pair<float, char> >vec;
	for (int i = 0; i < num; i++)
	{
		auto tmp = queue.top();
		vec.push_back(tmp);
		queue.pop();
	}
	return vec;	
}

const vector<pair<float, char> > Voc::getnextn(char c, int num) 
{
	if (c == this->separator)
	{
		clearprefix();
	}
	else {
		prefix += c;
	}
	return getnextn(prefix, num);
}


/*
int vocmain()
{
	cout << "init() start" << endl;
	voc.init();
	cout << "init() done" << endl;
	while (1)
	{
		char prefix;
		cin >> prefix;
		cout << "get " << prefix << endl;
		voc.debug(prefix, 5);
	}
	return 0;
}
*/