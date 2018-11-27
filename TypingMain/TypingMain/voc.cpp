// voc.cpp: 定义控制台应用程序的入口点。
//
//#include "stdafx.h"
#include <nlohmann/json.hpp>
#include <fstream>
#include <iostream>
#include <string>
#include <queue>

using json = nlohmann::json;
using namespace std;
class Voc {
private:
	json data;
	string prefix;
	const char separator = '.';//分隔符，实测时为空格
	int allfreq = 0;//所有开头字母的频数
	const string datapath = "./data/prefix";
protected:
	int getFreq(string prefix)
	{
		if (prefix == "") return getAllFreq();
		if (data.count(prefix) == 0) return 0;
		return data[prefix];
	}
	int getAllFreq()
	{
		return allfreq ? allfreq : 1;
	}
public:
	void clearall()
	{
		data = NULL;
		allfreq = 0;
		prefix = "";
	}
	void clearprefix()
	{
		prefix = "";
	}
	void init()
	{
		clearall();
		ifstream i(datapath);
		i >> data;
		for (char i = 'a'; i <= 'z'; i++)
		{
			this->allfreq += getFreq("" + i);
		}
	}
	/** 根据输入的prefix得到下一个备选字母和频率（num个备选）
	@ret [(freq,char)]
	*/
	const vector<pair<float, char> > getnextn(string prefix, int num)
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
	/* 自动记录符号累计，得到备选num个,如果c是" "，清空累计
	*/
	const vector<pair<float, char> > getnextn(char c, int num) {
		if (c == this->separator)
		{
			clearprefix();
		}
		else {
			prefix += c;
		}
		return getnextn(prefix, num);
	}
	void debug(string prefix, int num)
	{
		for (auto e : getnextn(prefix, num))
		{
			cout << e.first << " " << e.second << endl;
		}
	}
	void debug(char c, int num)
	{
		for (auto e : getnextn(c, num))
		{
			cout << e.first << " " << e.second << endl;
		}
		cout << "now the accPrefix is " << this->prefix << endl;
	}
}voc;
int main()
{
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

