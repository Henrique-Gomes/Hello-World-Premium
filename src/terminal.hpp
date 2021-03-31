#include <iostream>
#include <vector>
#include <string>
#include <map>
#ifdef _WIN32
	#include <Windows.h>
#endif

extern std::map<std::string, int> colorNames;
extern std::map<std::string, int> punctuationNames;

std::string getPossibleOptions(std::map<std::string, int>& map);

void colorError();
int parseColor(std::vector<std::string>::iterator& it, std::vector<std::string>::iterator end);

void formatText(int color, int backColor, bool underline);

void punctuationError();
int parsePunctuation(std::vector<std::string>::iterator& it, std::vector<std::string>::iterator end);