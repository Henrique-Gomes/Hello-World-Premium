#include <iostream>
#include <string>

#include "terminal.hpp"

void showConsoleError(std::string error) {
	formatText(31,false);
	
	std::cerr << "Error: " << error <<  std::endl;

	std::cout << "\033[0m";
}