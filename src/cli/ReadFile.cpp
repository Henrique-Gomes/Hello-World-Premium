#include <iostream>
#include <stdint.h>
#include <fstream>

#include "HWP.h"

/*

		.hwp file structure v1
	
	┌───────────────────────┬─────────────┬───────────────────────┐
	│ NAME                  │ SIZE (bits) │ DESCRIPTION           │
	├───────────────────────┼─────────────┼───────────────────────┤
	│ Header                │          48 │                       │
	├─┬─────────────────────┼─────────────┼───────────────────────┤
	│ │ Signature           │          32 │ ".HWP"                │
	├─┼─────────────────────┼─────────────┼───────────────────────┤
	│ │ Version             │          16 │ uint16_t              │
	├─┴─────────────────────┼─────────────┼───────────────────────┤
	│ Raw Data              │          24 │                       │
	├─┬─────────────────────┼─────────────┼───────────────────────┤
	│ │ Color               │           5 │                       │
	├─┼─────────────────────┼─────────────┼───────────────────────┤
	│ │ Case                │           3 │                       │
	├─┼─────────────────────┼─────────────┼───────────────────────┤
	│ │ Back Color          │           5 │                       │
	├─┼─────────────────────┼─────────────┼───────────────────────┤
	│ │ Help                │           1 │                       │
	├─┼─────────────────────┼─────────────┼───────────────────────┤
	│ │ Underline           │           1 │                       │
	├─┼─────────────────────┼─────────────┼───────────────────────┤
	│ │ Stay Open           │           1 │                       │
	├─┼─────────────────────┼─────────────┼───────────────────────┤
	│ │ Punctuation         │           2 │                       │
	├─┼─────────────────────┼─────────────┼───────────────────────┤
	│ │ Separator           │           4 │                       │
	├─┼─────────────────────┼─────────────┼───────────────────────┤
	│ │ Offset              │           1 │                       │
	└─┴─────────────────────┴─────────────┴───────────────────────┘	
	
*/

void readFile(char* path);
void processFile(uint16_t version, std::istream& file, int& argc, char**& argv);
void processFileV1(std::istream& file, int& argc, char**& argv);
void setBoolParam(char* s, bool b, char p);

void readFile(char* path) {
	
	int argc;
	char** argv;
	
	char buffer[4];
    std::ifstream file;
	file.open(path, std::ios::in | std::ios::binary);
    if (!file.is_open()) {
		fatalError("Access denied.");
		return;
    }
	
	// reading signature
    if(!file.read (buffer, 4)){
		fatalError("Incomplete file. Truncated at: header.");
		return;
	}
	if (!((buffer[0] == '.') && (buffer[0] == 'H') && (buffer[0] == 'W') && (buffer[0] == 'P'))) {
		fatalError("Not a .hwp file.");
		return;
	}
	
	// reading version
    if(!file.read (buffer, 2)){
		fatalError("Incomplete file. Truncated at: version.");
		return;
	}
	// proceeding to proper version handler
	processFile(buffer[1]+256*buffer[0], file, argc, argv);
	
    file.close();
}

void processFile(uint16_t version, std::istream& file, int& argc, char**& argv) {
	switch(version) {
		case 1:
			processFileV1(file, argc, argv);
			break;
		default:
			fatalError("Unsopported .hwp version. Get an update on https://github.com/Henrique-Gomes/Hello-World-Premium");
	}
}

void setBoolParam(char* s, bool b, char p){
	if (b)
		sprintf(s,"-%c True",p);
	else
		sprintf(s,"-%c False",p);
}

void processFileV1(std::istream& file, int& argc, char**& argv) {
	char buffer[3];
	
	argc=8;
	argv = (char**)malloc(8*sizeof(char*));
	
	// reading boolean parameters
    if(!file.read (buffer, 3)){
		fatalError("Incomplete file. Truncated at: Raw Data.");
		return;
	}

	sprintf(argv[0],"-c %d",(uint16_t)((buffer[0] & 0xF8) >> 3));
	sprintf(argv[1],"-a %d",(uint16_t)(buffer[0] & 0x07));
	sprintf(argv[2],"-b %d",(uint16_t)((buffer[1] & 0xF8) >> 3));
	
	setBoolParam(argv[3], buffer[1] & 0x04, 'h');
	setBoolParam(argv[4], buffer[1] & 0x02, 'u');
	setBoolParam(argv[5], buffer[1] & 0x01, 'o');
	
	sprintf(argv[6],"-p %d",(uint16_t)(buffer[4] & 0xC0));
	sprintf(argv[7],"-s %d",(uint16_t)(buffer[5] & 0x3C));
}