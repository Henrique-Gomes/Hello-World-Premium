#include "Formatter.h"

#include <iostream> // for cout

#ifdef _WIN32
	#include <Windows.h>
#endif

void Formatter::init() {
	#ifdef _WIN32
		// Enable Windows ANSI escape codes
		HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
		DWORD dwMode = 0;
		GetConsoleMode(hOut, &dwMode);
		dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
		SetConsoleMode(hOut, dwMode);
	#endif
}

void Formatter::setFormat(int color, int backColor, bool underline) {
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

void Formatter::resetFormat() {
	std::cout << "\033[0m";
}