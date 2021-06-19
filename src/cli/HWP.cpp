#include "HWP.h"
#include "ArgumentParser.h"
#include "Formatter.h"

#include <algorithm> // for transform
#include <iostream> // for cout
#include <map>
#include <random>
#include <string>
#include <vector>
#include <regex> // for string is number verification

#include <cctype> // for toupper
#include <cstdlib> // for exit

#ifdef _WIN32
#include <Windows.h> // for Sleep
#else
#include <unistd.h> // for Sleep
#endif
#include <bits/stdc++.h> // for MIN_INT and MAX_INT

#define MISSING_ARGUMENT INT_MIN
#define UNKOWN_ARGUMENT  INT_MIN+1

std::map<std::string, int> HWP::boolean = {
	{"true", 1},
	{"false", 0},
	{"True", 1},
	{"False", 0},
	{"TRUE", 1},
	{"FALSE", 0},
	{"truen't", 0},
	{"falsen't", 1},
	{"Truen't", 0},
	{"Falsen't", 1},
	{"TRUEN'T", 0},
	{"FALSEN'T", 1},
	{"t", 1},
	{"f", 0},
	{"T", 1},
	{"F", 0},
	{"yes", 1},
	{"no", 0},
	{"Yes", 1},
	{"No", 0},
	{"YES", 1},
	{"NO", 0},
	{"y", 1},
	{"n", 0},
	{"Y", 1},
	{"N", 0},
	{"yesn't", 0},
	{"non't", 1},
	{"Yesn't", 0},
	{"Non't", 1},
	{"YESN'T", 0},
	{"NON'T", 1},
	{"0", 0},
	{"1", 1},
	{"0x0", 0},
	{"0x1", 1}
};

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

std::map<std::string, int> HWP::separatorNames = {
	{"none", 0},
	{"commaspace", 1},
	{"semicolonspace", 2},
	{"hyphen", 3},
	{"underscore", 4},
	{"linefeed", 5},
	{"carriagereturn", 6},
	{"zerowidthspace", 7}, // 8203
	{"space", 8},
};

std::random_device HWP::randomDevice;
std::default_random_engine HWP::randomGenerator(HWP::randomDevice());
std::uniform_int_distribution<int> HWP::randomDistribution(0, 1);

HWP::HWP() {
	Formatter::init();
}

void HWP::parseCliArguments(int argc, char* argv[]) {

	ArgumentParser p(argc, argv);
	
	int subArgument;

	while (p.current != p.end) {
		std::string arg(*p.current);

		if (arg == "--help" || arg == "-h") {
			subArgument = parseNamedOption(p, arg, boolean, false);
			if ((subArgument == 1) || (subArgument == MISSING_ARGUMENT))
				printHelp();

		} else if (arg == "--color" || arg == "-c") {
			color = parseNamedOption(p, arg, colorNames);
			textFormatting = true;

		} else if (arg == "--back-color" || arg == "-b") {
			backColor = parseNamedOption(p, arg, colorNames) + 10;
			textFormatting = true;
		
		} else if (arg == "--underline" || arg == "-u") {
			subArgument = parseNamedOption(p, arg, boolean, false);
			if ((subArgument == 1) || (subArgument == MISSING_ARGUMENT)) {
				underline = true;
				textFormatting = true;
			}
		
		} else if (arg == "--punctuation" || arg == "-p") {
			punctuation = parseNamedOption(p, arg, punctuationNames);
		
		} else if (arg == "--case" || arg == "-a") {
			case_ = parseNamedOption(p, arg, caseNames);

		} else if (arg == "--separator" || arg == "-s") {
			separator = parseNamedOption(p, arg, separatorNames);
		
		} else if (arg == "--open" || arg == "-o") {
			subArgument = parseNamedOption(p, arg, boolean, false);
			stayOpen = ((subArgument == 1) || (subArgument == MISSING_ARGUMENT));
		
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
	std::cout << "    -s, --separator <separator-name>       Change the separator between the two words.\n";
	std::cout << "    -o, --open <boolean>                   Stay open.\n";
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
	std::cout << "<separator-name> values:\n";
	std::cout << "    ";
	std::cout << getNamedOptions(separatorNames);
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

int HWP::parseNamedOption(ArgumentParser& p, std::string& arg, std::map<std::string, int>& names, bool throwError) {
	if (!p.next()) {
		if (throwError)
			fatalError(arg + " requires one argument\n");
		else
			return MISSING_ARGUMENT;
	}

	auto pair = names.find(*p.current);

	if (std::regex_match(*p.current, std::regex("[(-|+)|][0-9]+")))
		return atoi(*p.current);
	
	if (pair == names.end()) {
		if (throwError)
			fatalError(arg + " be must one of these values:\n    " + getNamedOptions(names));
		else
			return UNKOWN_ARGUMENT;
	}

	return pair->second;
}

//

void HWP::printHelloWorld() {
	if (textFormatting) {
		Formatter::setFormat(color, backColor, underline);
	}

	std::string hello = "hello";
	std::string world = "world";

	switch (case_) {
		case 0: // sentence
			hello[0] = std::toupper(hello[0]);
			break;
		case 1: // upper
			std::transform(hello.begin(), hello.end(), hello.begin(), (int (*)(int))std::toupper);
			std::transform(world.begin(), world.end(), world.begin(), (int (*)(int))std::toupper);
			break;
		case 2: // lower
			break;
		case 3: // title
			hello[0] = std::toupper(hello[0]);
			world[0] = std::toupper(world[0]);
			break;
		case 4: // camel
			world[0] = std::toupper(world[0]);
			break;
		case 5: // wacky
			{
				bool upper = false;
				stringWackyfy(hello, upper);
				stringWackyfy(world, upper);
			}
			break;
		case 6: // random
			stringRandomize(hello);
			stringRandomize(world);
			break;
	}

	std::string helloWorld = hello;

	switch (separator) {
		case 0: break;
		case 1: helloWorld += ", ";
			break;
		case 2: helloWorld += "; ";
			break;
		case 3: helloWorld += "-";
			break;
		case 4: helloWorld += "_";
			break;
		case 5: helloWorld += "\n";
			break;
		case 6: helloWorld += "\r";
			break;
		case 7: helloWorld += "​";
			break;
		case 8:	helloWorld += " ";
			break;
	}

	helloWorld += world;

	switch (punctuation) {
		case 0: break;
		case 1: helloWorld += "!";
			break;
		case 2: helloWorld += ".";
			break;
		case 3: helloWorld += "‽";
			break;
	}

	std::cout << helloWorld;
	std::cout << "\n";

	if (textFormatting) {
		Formatter::resetFormat();
	}

	if (stayOpen)
		while(true)
			Sleep(INT_MAX);
}

void HWP::stringWackyfy(std::string& str, bool& upper) {
	for (std::string::reference c : str) {
		if (upper) {
			c = std::toupper(c);
		}
		upper = !upper;
	}
}

void HWP::stringRandomize(std::string& str) {
	for (std::string::reference c : str) {
		bool upper = (bool) randomDistribution(randomGenerator);
		if (upper) {
			c = std::toupper(c);
		}
	}
}

//

void fatalError(std::string error) {
	Formatter::setFormat(31, 0, false);
	std::cerr << error;
	Formatter::resetFormat();
	std::exit(1);
}