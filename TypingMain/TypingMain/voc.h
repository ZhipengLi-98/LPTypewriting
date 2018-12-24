#pragma once

#include <nlohmann/json.hpp>
#include <fstream>
#include <iostream>
#include <string>
#include <queue>

using json = nlohmann::json;
//using namespace std;

#define DEBUG 1
struct AssociWords {
	std::vector<std::pair<float, std::string> > alphas;
	std::vector<std::pair<float, std::string> > words;
	std::vector<std::pair<float, std::string> > firstAlphas;
};

class Voc {
private:
	json data;
	std::string prefix;
	const char separator = '.';//分隔符，实测时为空格
	int allfreq = 0;//所有开头字母的频数
	const std::string datapath = "./data/prefix";
protected:
	int getFreq(std::string prefix);
	int getAllFreq();
public:
	void clearall();
	void clearprefix();

	void init();
	/** 根据输入的prefix得到下一个备选字母和频率（num个备选）
	@ret [(freq,char)]
	*/
	const std::vector<std::pair<float, char> > getnextn(std::string prefix, int num);

	/* 自动记录符号累计，得到备选num个,如果c是" "，清空累计
	*/
	const std::vector<std::pair<float, char> > getnextn(char c, int num);
	void debug(std::string prefix, int num);
	void debug(char c, int num);
};