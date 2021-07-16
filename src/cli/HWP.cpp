#include "HWP.h"
#include "ArgumentParser.h"
#include "Formatter.h"

#include <common/Common.h>

#include <algorithm> // for transform
#include <iostream> // for cout
#include <map>
#include <random>
#include <ranges>
#include <string>
#include <vector>

#include <cctype> // for toupper
#include <cstdlib> // for exit

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

		} else if (arg == "--separator" || arg == "-s") {
			separator = parseNamedOption(p, arg, separatorNames);

		} else if (arg == "--quantity" || arg == "-q") {
			quantity = parseIntOption(p, arg);
			textFormatting = true;
		
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
	std::cout << "    -q, --quantity <integer>               Repeat a quantity of times.\n";
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

int HWP::parseIntOption(ArgumentParser& p, std::string& arg) {
	if (!p.next()) {
		fatalError(arg + " requires one argument\n");
	}

	std::string valueString(*p.current);

	int value;
	size_t afterIndex;

	try {
		value = std::stoi(valueString, &afterIndex);
	} catch (std::invalid_argument& e) {
		fatalError(valueString + " is not an integer\n");
	} catch (std::out_of_range& e) {
		fatalError(valueString + " is too much\n");
	}

	if (value < 0) {
		fatalError(std::to_string(value) + " is not a positive integer\n");
	}

	// If there's characters after the number
	if (afterIndex != valueString.size()) {
		fatalError(valueString + " is not an integer\n");
	}

	return value;
}

//

void HWP::printHelloWorld() {
	if (textFormatting) {
		Formatter::setFormat(color, backColor, underline);
	}

	std::string hello = Common::hello;
	std::string world = Common::world;

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

	for (int i : std::ranges::iota_view{0, quantity}) {
		std::cout << helloWorld;
		std::cout << "\n";
	}

	if (textFormatting) {
		Formatter::resetFormat();
	}
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

void HWP::fatalError(std::string error) {
	Formatter::setFormat(31, 0, false);
	std::cerr << error;
	Formatter::resetFormat();
	std::exit(1);
}