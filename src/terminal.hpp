#include <iostream>
#include <vector>
#include <string>
#include <map>
#ifdef _WIN32
	#include <Windows.h>
#endif

void printPossibleColors();
void colorError();
int parseColor(std::vector<std::string>::iterator it, std::vector<std::string>::iterator end);
void formatText(int color, int backColor, bool underline);