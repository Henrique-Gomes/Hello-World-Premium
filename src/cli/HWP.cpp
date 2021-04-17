#include "HWP.h"
#include "ArgumentParser.h"
#include "Formatter.h"

#include <iostream> // for cout
#include <map>
#include <string>
#include <vector>

#include <cctype> // for tolower
#include <cstdlib> // for srand, rand, exit
#include <ctime> // for time

std::map<std::string, int> HWP::colorNames = {
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

std::map<std::string, int> HWP::punctuationNames = {
	{"none", 0},
	{"!", 1},
	{".", 2},
	{"‽", 3},
	// {"exclamation", 1},
	// {"period", 2},
	// {"interrobang", 3},
};

std::map<std::string, int> HWP::caseNames = {
	{"sentence", 0}, // Hello, world!
	{"upper", 1}, // HELLO, WORLD!
	{"lower", 2}, // hello, world!
	{"title", 3}, // Hello, World!
	{"camel", 4}, // hello, World!
	{"wacky", 5}, // hElLo, WoRlD!
	{"random", 6},
};

HWP::HWP() {
	Formatter::init();
}

void HWP::parseCliArguments(int argc, char* argv[]) {

	ArgumentParser p(argc, argv);

	while (p.current != p.end) {
		std::string arg(*p.current);

		if (arg == "--help" || arg == "-h") {
			printHelp();

		} else if (arg == "--color" || arg == "-c") {
			color = parseNamedOption(p, arg, colorNames);
			textFormatting = true;

		} else if (arg == "--back-color" || arg == "-b") {
			backColor = parseNamedOption(p, arg, colorNames) + 10;
			textFormatting = true;
		
		} else if (arg == "--underline" || arg == "-u") {
			underline = true;
			textFormatting = true;
		
		} else if (arg == "--punctuation" || arg == "-p") {
			punctuation = parseNamedOption(p, arg, punctuationNames);
		
		} else if (arg == "--case" || arg == "-a") {
			case_ = parseNamedOption(p, arg, caseNames);
		
		} else {
			fatalError("No argument called " + arg + "\n");

		}

		p.next();

	}
}

void HWP::printHelp() {
	std::cout << "Hello World Premium\n";
	std::cout << "\n";
	std::cout << "Options:\n";
	std::cout << "    -h, --help                             Show help text.\n";
	std::cout << "    -c, --color <color-name>               Change the color of the text.\n";
	std::cout << "    -b, --back-color <color-name>          Change the background color of the text.\n";
	std::cout << "    -u, --underline                        Add underline to the text.\n";
	std::cout << "    -p, --punctuation <punctuation-name>   Change the final punctuation of the text.\n";
	std::cout << "    -a, --case <case-name>                 Change the case of the text.\n";
	std::cout << "\n";
	std::cout << "<color-name> values:\n";
	std::cout << "    ";
	std::cout << getNamedOptions(colorNames);
	std::cout << "\n";
	std::cout << "<punctuation-name> values:\n";
	std::cout << "    ";
	std::cout << getNamedOptions(punctuationNames);
	std::cout << "\n";
	std::cout << "<case-name> values:\n";
	std::cout << "    ";
	std::cout << getNamedOptions(caseNames);
	std::cout << "\n";

	std::exit(0);
}

std::string HWP::getNamedOptions(std::map<std::string, int>& map) {
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

int HWP::parseNamedOption(ArgumentParser& p, std::string& arg, std::map<std::string, int>& names) {
	if (!p.next()) {
		fatalError(arg + " requires one argument\n");
	}

	auto pair = names.find(*p.current);
	if (pair == names.end()) {
		fatalError(arg + " be must one of these values:\n    " + getNamedOptions(names));
	}

	return pair->second;
}

//

void HWP::printHelloWorld() {
	if (textFormatting) {
		Formatter::setFormat(color, backColor, underline);
	}

	std::string helloWorld = "HELLO, WORLD";;

	switch (case_) {
		case 0: helloWorld = "Hello, world";
			break;
		case 1: break;
		case 2: helloWorld = "hello, world";
			break;
		case 3: helloWorld = "Hello, World";
			break;
		case 4: helloWorld = "hello, World";
			break;
		case 5: helloWorld = "hElLo, WoRlD";
			break;
		case 6:
			std::srand(std::time(0));
			for (std::string::reference c : helloWorld) {
				if ((std::rand() % 2) == 0) {
					c = std::tolower(c);
				}
			}
			break;
	}

	std::cout << helloWorld;

	switch (punctuation) {
		case 0: break;
		case 1: std::cout << "!";
			break;
		case 2: std::cout << ".";
			break;
		case 3: std::cout << "‽";
			break;
	}

	std::cout << "\n";

	if (textFormatting) {
		Formatter::resetFormat();
	}
}

//

void HWP::fatalError(std::string error) {
	Formatter::setFormat(31, 0, false);
	std::cerr << error;
	Formatter::resetFormat();
	std::exit(1);
}