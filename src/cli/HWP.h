#pragma once

#include "ArgumentParser.h"

#include <map>
#include <string>
#include <vector>

class HWP {

public:

	static std::map<std::string, int> colorNames;
	static std::map<std::string, int> punctuationNames;
	static std::map<std::string, int> caseNames;

	bool textFormatting = false;

	int color = 0;
	int backColor = 0;
	bool underline = false;
	int punctuation = 1;
	int case_ = 0;

	HWP();

	void parseCliArguments(int argc, char* argv[]);
	void printHelp();
	std::string getNamedOptions(std::map<std::string, int>& map);
	int parseNamedOption(ArgumentParser& p, std::string& arg, std::map<std::string, int>& names);

	void printHelloWorld();
	void formatText(int color, int backColor, bool underline);

	void fatalError(std::string error);

};