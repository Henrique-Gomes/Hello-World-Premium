// main.cpp

#include "HWP.h"

int main(int argc, char* argv[]) {
	
	HWP hwp;
	hwp.parseCliArguments(argc, argv);
	hwp.printHelloWorld();

	return 0;
}