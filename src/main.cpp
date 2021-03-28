#include <iostream>
#include <vector>
#include <string>
#include <stdexcept>
#include <cstdlib>

#ifdef _WIN32
	#include <Windows.h>
#endif

int main(int argc, char* argv[]);
void colorError();

int main(int argc, char* argv[]) {

	bool textFormatting = false;

	int color = 0;
	bool underline = false;

	std::vector<std::string> unparsedArgs(argv + 1, argv + argc);

	for (std::vector<std::string>::iterator it = unparsedArgs.begin(); it != unparsedArgs.end(); ++it) {
		size_t index = std::distance(unparsedArgs.begin(), it);

		// std::cout << "[DEBUG] " << index << ": " << *it << "\n";

		if (*it == "--color" || *it == "-c") {

			std::string arg = *it;

			++it;
			if (it == unparsedArgs.end()) {
				std::cout << "Error: " << arg << " requeries one argument\n";
				return 1;
			}

			int argColor;

			try {
				argColor = std::stoi(*it);
			} catch (std::invalid_argument& e) {
				colorError();
			} catch (std::out_of_range& e) {
				colorError();
			}
			
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

void colorError() {
	std::cout << "Error: Color must be a number between 30 and 37 or between 90 and 97\n";
	std::exit(1);
}