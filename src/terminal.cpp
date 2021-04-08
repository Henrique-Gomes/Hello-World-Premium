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

std::map<std::string, int> punctuationNames = {
	{"none", 0},
	{"!", 1},
	{".", 2},
	{"‽", 3},
	// {"exclamation", 1},
	// {"period", 2},
	// {"interrobang", 3},
};

std::map<std::string, int> caseNames = {
	{"sentence", 0}, // Hello, world!
	{"upper", 1}, // HELLO, WORLD!
	{"lower", 2}, // hello, world!
	{"title", 3}, // Hello, World!
	{"camel", 4}, // hello, World!
	{"wacky", 5}, // hElLo, WoRlD!
	{"random", 6},
};

std::string getPossibleOptions(std::map<std::string, int>& map) {
	int i = 0;
	std::string s = "";

	for (const auto& pair : map) {
		s += pair.first;
		if (i != map.size() - 1) {
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
		getPossibleOptions(colorNames));
	std::exit(1);
}

int parseColor(std::vector<std::string>::iterator& it, std::vector<std::string>::iterator end) {
	std::string arg = *it;

	++it;
	if (it == end) {
		showConsoleError(arg + " requires one argument\n");
		std::exit(1);
	}

	auto pair = colorNames.find(*it);
	if (pair == colorNames.end()) {
		colorError();
	}

	return pair->second;
}

void formatText(int color, int backColor, bool underline) {
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

	if (backColor != 0) {
		std::cout << ";" << backColor;
	}

	if (underline) {
		std::cout << ";4";
	}

	std::cout << "m";
}

void punctuationError() {
	showConsoleError("Punctuation be must one of these values:\n    " +
		getPossibleOptions(punctuationNames));
	std::exit(1);
}

int parsePunctuation(std::vector<std::string>::iterator& it, std::vector<std::string>::iterator end) {
	std::string arg = *it;

	++it;
	if (it == end) {
		showConsoleError(arg + " requires one argument\n");
		std::exit(1);
	}

	auto pair = punctuationNames.find(*it);
	if (pair == punctuationNames.end()) {
		punctuationError();
	}

	return pair->second;
}

void caseError() {
	showConsoleError("Case be must one of these values:\n    " +
		getPossibleOptions(caseNames));
	std::exit(1);
}

int parseCase(std::vector<std::string>::iterator& it, std::vector<std::string>::iterator end) {
	std::string arg = *it;

	++it;
	if (it == end) {
		showConsoleError(arg + " requires one argument\n");
		std::exit(1);
	}

	auto pair = caseNames.find(*it);
	if (pair == caseNames.end()) {
		caseError();
	}

	return pair->second;
}