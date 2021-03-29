#include <iostream>
#include <string>

#include "terminal.hpp"

void showConsoleError(std::string error) {
	formatText(31, 0, false);
	
	std::cerr << "Error: " << error;

	std::cout << "\033[0m";
}