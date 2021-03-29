#include <iostream>
#include <vector>
#include <string>
#include <stdexcept>
#include <cstdlib>
#include <map>

#ifdef _WIN32
	#include <Windows.h>
#endif

int main(int argc, char* argv[]);
void printPossibleColors();
void colorError();

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

			std::string arg = *it;

			++it;
			if (it == unparsedArgs.end()) {
				std::cout << "Error: " << arg << " requires one argument\n";
				return 1;
			}

			auto pair = colorNames.find(*it);
			if (pair == colorNames.end()) {
				colorError();
			}

			int argColor = pair->second;
			
			if (!((argColor >= 30 && argColor <= 37) || (argColor >= 90 && argColor <= 97))) {
				colorError();
			}

			textFormatting = true;
			color = argColor;

		} else if (*it == "--underline" || *it == "-u") {

			textFormatting = true;
			underline = true;

		} else {
			std::cout << "Error: No argument called " << *it << "\n";
			std::exit(1);
		}

	}

	if (textFormatting) {
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

	std::cout << "Hello, world!" << std::endl;

	if (textFormatting) {
		std::cout << "\033[0m";
	}

	return 0;
}

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

void colorError() {
	std::cout << "Error: Color be must one of these values:\n";
	std::cout << "    ";
	printPossibleColors();
	std::exit(1);
}