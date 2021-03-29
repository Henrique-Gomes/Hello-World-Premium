#include <iostream>
#include <vector>
#include <string>
#include <map>
#include "terminal.hpp"
#include "error.hpp"

int main(int argc, char* argv[]) {

	bool textFormatting = false;

	int color = 0;
	bool underline = false;

	std::vector<std::string> unparsedArgs(argv + 1, argv + argc);

	for (std::vector<std::string>::iterator it = unparsedArgs.begin(); it != unparsedArgs.end(); ++it) {

		if (*it == "--help" || *it == "-h") {
			std::cout << "Hello World Premium\n\n";
			std::cout << "Options:\n\n";
			std::cout << "    --help/-h            Show help text.\n";
			std::cout << "    --colors/-c <name>   Change the color of the text. Possible values:\n";
			std::cout << "        ";
			printPossibleColors();
			std::cout << "\n";
			std::cout << "    --underline/-u       Add underline to the text.\n";

			std::exit(0);

		} else if (*it == "--color" || *it == "-c") {
			color = parseColor(it,unparsedArgs.end());
			textFormatting = true;

		} else if (*it == "--underline" || *it == "-u") {
			textFormatting = true;
			underline = true;

		} else if ((*it)[0] == '-') {
			showConsoleError("No argument called " + *it + "\n");
			std::exit(1);
		}
	}
	
	// TODO: criar objeto com argumentos de formatação

	if (textFormatting) {
		formatText(color,underline);
	}

	std::cout << "Hello, world!" << std::endl;

	if (textFormatting) {
		std::cout << "\033[0m";
	}

	return 0;
}