//
// Created by mscheman on 9/6/24.
//

#ifndef CPP_CONSTRUCTOR
#define CPP_CONSTRUCTOR

#include <iostream>
#include <fstream>
#include <string>
#include <sys/stat.h>
#include <cstdlib>
#include <vector>

#include "colors.h"

#define OUTPUT_DIR "output"

class ClassInfo;

class CPP_Constructor {
private:
	std::vector<ClassInfo*, std::allocator<ClassInfo*>> _classes;
	void _printHelp();
	void _createClass();
	void _printClasses();
	void _editClass();
	void _exportClass();
	void _writeH(ClassInfo *classInfo);
	void _writeCPP(ClassInfo *classInfo);
public:
	void createOutputDir();
	void shellStart();
};

std::string	userInput(const std::string &msg, bool(*check)(std::string));
bool		userInputBypass(std::string);

#endif //CPP_CONSTRUCTOR
