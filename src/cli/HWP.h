#pragma once

#include "ArgumentParser.h"

#include <map>
#include <random>
#include <string>
#include <vector>

class HWP {

public:

	static std::map<std::string, int> colorNames;
	static std::map<std::string, int> punctuationNames;
	static std::map<std::string, int> caseNames;
	static std::map<std::string, int> separatorNames;
	static std::map<std::string, int> boolean;

	static std::random_device randomDevice;
	static std::default_random_engine randomGenerator;
	static std::uniform_int_distribution<int> randomDistribution;

	bool textFormatting = false;

	int color = 0;
	int backColor = 0;
	bool underline = false;
	int punctuation = 1;
	int case_ = 0;
	int separator = 1;
	bool stayOpen = false;

	HWP();

	void parseCliArguments(int argc, char* argv[]);
	void printHelp();
	std::string getNamedOptions(std::map<std::string, int>& map);
	int parseNamedOption(ArgumentParser& p, std::string& arg, std::map<std::string, int>& names, bool throwError = true);

	void printHelloWorld();
	void stringWackyfy(std::string& str, bool& upper);
	void stringRandomize(std::string& str);

	void fatalError(std::string error);

};