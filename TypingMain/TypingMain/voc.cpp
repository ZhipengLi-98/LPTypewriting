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
	if (wordPrefix.count(prefix) == 0) return 0;
	return wordPrefix[prefix];
}

int Voc::getAllFreq()
{
	return allfreq ? allfreq : 1;
}

const vector<pair<float, string> > Voc::getnextsingles(string prefix, int num)
	{
		priority_queue<pair<float, string> > queue;

		
		for (char i = 'a'; i <= 'z'; i++)
		{
			float nextFreq = getFreq(prefix + string(1,i));
			float rfreq = nextFreq==0?0 : float(nextFreq + 1) / (getFreq(prefix) + 26);
			queue.push(make_pair(rfreq, string(1, i)));
		}

		vector<pair<float, string> >vec;
		for (int i = 0; i < num; i++)
		{
			auto tmp = queue.top();
			if (tmp.first == 0) break;
			vec.push_back(tmp);
			queue.pop();
		}
		return vec;
	}

const vector<pair<float, string> > Voc::getnextwords(string prefix, int num)
	{
		priority_queue<pair<float, string> > queue;
		const vector<pair<float, string> > a;
		if (prefix2Word.find(prefix)==prefix2Word.end()) {
		
			return a;
		}
		vector<pair<float, string> >vec;
		int allnum = 0;
		for (string word : prefix2Word[prefix])
		{
			allnum += wordFreq[word];
		}
		for (string word : prefix2Word[prefix])
		{
			queue.push(make_pair((float)wordFreq[word] / allnum, word));
		}
		for (int i = 0; (!queue.empty())&&(i < num) ; i++)
		{
			auto tmp = queue.top();
			vec.push_back(tmp);
			queue.pop();
		}
		return vec;
	}

void Voc::clearall()
{
	wordPrefix = NULL;
	allfreq = 0;
	wordFreq = NULL;
	prefix2Word = NULL;
}
/*
void Voc::clearprefix()
{
	prefix = "";
}
*/

void Voc::init()
{
	/*
	clearall();
	ifstream i(datapath);
	i >> data;
	for (char i = 'a'; i <= 'z'; i++)
	{
		this->allfreq += getFreq("" + i);
	}
	*/	
clearall();
		ifstream i(wordPrefixPath);
		i>> wordPrefix;
#if DEBUG
		cout << "Load wordPrefix done" << endl;
#endif
		ifstream ifsw(wordFreqPath);
		ifsw >> wordFreq;
#if DEBUG
		cout << "Load wordFreq done" << endl;
#endif
		ifstream ifsp(prefix2WordPath);
		ifsp >> prefix2Word;
#if DEBUG
		cout << "Load prefix2Word done" << endl;
#endif

		for (char i = 'a'; i <= 'z'; i++)
		{
			this->allfreq += getFreq(string(1,i));
		}	
}

AssociWords Voc::getnexts(string prefix, int alphaNum, int wordNum)
	{
		AssociWords associWords;
		associWords.alphas = getnextsingles(prefix, alphaNum);
		if (associWords.alphas.size() < alphaNum)
		{
			wordNum += alphaNum - associWords.alphas.size();
		}
		associWords.words = getnextwords(prefix, wordNum);
		if (associWords.words.size() < wordNum)
		{
			associWords. firstAlphas = getnextsingles("", wordNum - associWords. words.size());
		}
		return associWords;
	}

void Voc::debug(string prefix, int alphaNum, int wordNum)
	{
		cout << "--------singles----" << endl;
		for (auto e : getnextsingles(prefix, alphaNum))
		{
			cout << e.first << " " << e.second << endl;
		}
		cout << "--------words" << endl;
		for (auto e : getnextwords(prefix, wordNum))
		{
			cout << e.first << " " << e.second << endl;
		}
		cout << "--------singles & words" << endl;
		AssociWords a= getnexts(prefix, alphaNum, wordNum);
		for (auto e : a.alphas )
		{
			cout << e.first << " " << e.second << endl;
		}
		for (auto e : a.words)
		{
			cout << e.first << " " << e.second << endl;
		}
		for (auto e : a.firstAlphas)
		{
			cout << e.first << " " << e.second << endl;
		}
	}

Voc voc;
int tempmain()
{
	voc.init();
	cout << "init() done" << endl;
	while (1)
	{
		string prefix;
		cin >> prefix;
		cout << "get " << prefix << endl;
		voc.debug(prefix, 5,3);
		
	}
    return 0;
}


/*
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
*/
/*
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
*/

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