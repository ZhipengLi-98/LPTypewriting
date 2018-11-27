// voc.cpp: �������̨Ӧ�ó������ڵ㡣
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
	const char separator = '.';//�ָ�����ʵ��ʱΪ�ո�
	int allfreq = 0;//���п�ͷ��ĸ��Ƶ��
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
	/** ���������prefix�õ���һ����ѡ��ĸ��Ƶ�ʣ�num����ѡ��
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
	/* �Զ���¼�����ۼƣ��õ���ѡnum��,���c��" "������ۼ�
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

