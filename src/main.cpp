#include <iostream>
#include <vector>
#include <string>
#include <map>
#include "terminal.hpp"
#include "error.hpp"

int main(int argc, char* argv[]) {

	bool textFormatting = false;

	int color = 0;
	int backColor = 0;
	bool underline = false;
	int punctuation = 1;

	std::vector<std::string> unparsedArgs(argv + 1, argv + argc);

	for (std::vector<std::string>::iterator it = unparsedArgs.begin(); it != unparsedArgs.end(); ++it) {

		if (*it == "--help" || *it == "-h") {
			std::cout << "Hello World Premium\n";
			std::cout << "\n";
			std::cout << "Options:\n";
			std::cout << "    -h, --help                             Show help text.\n";
			std::cout << "    -c, --color <color-name>               Change the color of the text.\n";
			std::cout << "    -b, --back-color <color-name>          Change the background color of the text.\n";
			std::cout << "    -u, --underline                        Add underline to the text.\n";
			std::cout << "    -p, --punctuation <punctuation-name>   Change the final punctuation of the text.\n";
			std::cout << "\n";
			std::cout << "<color-name> values:\n";
			std::cout << "    ";
			std::cout << getPossibleOptions(colorNames);
			std::cout << "\n";
			std::cout << "<punctuation-name> values:\n";
			std::cout << "    ";
			std::cout << getPossibleOptions(punctuationNames);
			std::cout << "\n";

			std::exit(0);

		} else if (*it == "--color" || *it == "-c") {
			textFormatting = true;
			color = parseColor(it, unparsedArgs.end());

		} else if (*it == "--back-color" || *it == "-b") {
			textFormatting = true;
			backColor = parseColor(it, unparsedArgs.end()) + 10;

		} else if (*it == "--underline" || *it == "-u") {
			textFormatting = true;
			underline = true;

		} else if (*it == "--punctuation" || *it == "-p") {
			punctuation = parsePunctuation(it, unparsedArgs.end());

		} else {
			showConsoleError("No argument called " + *it + "\n");
			std::exit(1);
		}
	}
	
	// TODO: criar objeto com argumentos de formatação

	if (textFormatting) {
		formatText(color, backColor, underline);
	}

	std::cout << "Hello, world";

	switch (punctuation) {
		case 0: break;
		case 1: std::cout << "!";
			break;
		case 2: std::cout << ".";
			break;
		case 3: std::cout << "‽";
			break;
	}

	std::cout << std::endl;

	if (textFormatting) {
		std::cout << "\033[0m";
	}

	return 0;
}