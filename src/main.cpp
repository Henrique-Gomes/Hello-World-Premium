#include <iostream>
#include <vector>
#include <string>

#ifdef _WIN32
#include <Windows.h>
#endif

int main(int argc, char* argv[]) {

	bool color = false;

	std::vector<std::string> unparsedArgs(argv + 1, argv + argc);

	for (std::vector<std::string>::iterator it = unparsedArgs.begin(); it != unparsedArgs.end(); ++it) {
		size_t index = std::distance(unparsedArgs.begin(), it);

		std::cout << "[DEBUG] " << index << ": " << *it << "\n";

		if (*it == "--color" || *it == "-c") {
			color = true;
		}

	}

	if (color) {
		#ifdef _WIN32
			HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
			DWORD dwMode = 0;
			GetConsoleMode(hOut, &dwMode);
			dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
			SetConsoleMode(hOut, dwMode);
		#endif

		std::cout << "\033[92m";
	}

	std::cout << "Hello, world!" << std::endl;

	if (color) {
		std::cout << "\033[0m";
	}
}