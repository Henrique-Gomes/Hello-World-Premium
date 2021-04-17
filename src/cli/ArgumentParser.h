#pragma once

class ArgumentParser {
	
public:
	int argc;
	char** argv;

	char** begin;
	char** end;
	char** current;

	ArgumentParser(int argc, char** argv);
	bool next();
	
};