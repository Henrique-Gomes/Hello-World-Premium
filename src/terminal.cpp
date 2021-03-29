#include <iostream>
#include <vector>
#include <string>
#include <map>
#ifdef _WIN32
	#include <Windows.h>
#endif

#include "error.hpp"

std::map<std::string, int> colorNames = {
	{"black", 30},
	{"maroon", 31},
	{"green", 32},
	{"olive", 33},
	{"navy", 34},
	{"purple", 35},
	{"teal", 36},
	{"silver", 37},
	{"gray", 90},
	{"red", 91},
	{"lime", 92},
	{"yellow", 93},
	{"blue", 94},
	{"fuschia", 95},
	{"aqua", 96},
	{"white", 97},
};

void printPossibleColors() {
	int i=0;
	for (const auto& pair : colorNames) {
		std::cout << pair.first;
		if (i != colorNames.size() - 1) {
			std::cout << ", ";
		} else {
			std::cout << "\n";
		}
		++i;
	}
}

std::string getPossibleColors() {
	int i=0;
	
	std::string s = "";
	
	for (const auto& pair : colorNames) {
		s += pair.first;
		if (i != colorNames.size() - 1) {
			s += ", ";
		} else {
			s += "\n";
		}
		++i;
	}
	
	return s;
}

void colorError() {
	showConsoleError("Color be must one of these values:\n    " +
		getPossibleColors());
	std::exit(1);
}

int parseColor(std::vector<std::string>::iterator it, std::vector<std::string>::iterator end) {
	std::string arg = *it;

	++it;
	if (it == end) {
		showConsoleError(arg + " requires one argument");
		std::exit(1);
	}

	auto pair = colorNames.find(*it);
	if (pair == colorNames.end()) {
		colorError();
	}

	int argColor = pair->second;
	
	if (!((argColor >= 30 && argColor <= 37) || (argColor >= 90 && argColor <= 97))) {
		colorError();
	}

	return argColor;
}

void formatText(int color, bool underline) {
	#ifdef _WIN32
		HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
		DWORD dwMode = 0;
		GetConsoleMode(hOut, &dwMode);
		dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
		SetConsoleMode(hOut, dwMode);
	#endif

	std::cout << "\033[";

	if (color != 0) {
		std::cout << color;
	}

	if (underline) {
		std::cout << ";4";
	}

	std::cout << "m";
}