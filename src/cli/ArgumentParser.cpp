#include "ArgumentParser.h"

ArgumentParser::ArgumentParser(int argc, char** argv) : argc(argc), argv(argv) {
	this->begin = argv+1;
	this->end = argv+argc;
	this->current = this->begin;
}

bool ArgumentParser::next() {
	++this->current;
	if (this->current >= this->end) {
		this->current = this->end;
		return false;
	}
	return true;
}