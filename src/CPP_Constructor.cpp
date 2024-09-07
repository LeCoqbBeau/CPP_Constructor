//
// Created by mscheman on 9/6/24.
//

#include "CPP_Constructor.h"
#include "AttributeInfo.h"
#include "ClassInfo.h"

void CPP_Constructor::createOutputDir() {
	struct stat sb;
	mkdir(OUTPUT_DIR, 0755);
	mkdir(OUTPUT_DIR "/src", 0755);
	mkdir(OUTPUT_DIR "/inc", 0755);
	if (stat(OUTPUT_DIR, &sb)
		|| stat(OUTPUT_DIR "/inc", &sb)
		|| stat(OUTPUT_DIR "/src", &sb))
	{
		std::cerr << BRED "Error creating the output folder." << std::endl;
		std::cerr << "Exiting program..." CLR << std::endl;
		exit(EXIT_FAILURE);
	}
}

void CPP_Constructor::shellStart(Setting setting) {
	std::string input;

	std::cout << std::endl;
	std::cout << BCYN "Welcome to CPP_Constructor by LeCoqBeau" CLR << std::endl;
	std::cout << std::endl;
	_printHelp();
	while (!std::cin.eof())
	{
		std::cout << " > ";
		std::getline(std::cin, input);
		if (input == "help")
			_printHelp();
		else if (input == "exit")
			break ;
		else if (input == "create")
			_createClass();
		else if (input == "print")
			_printClasses();
		else if (input == "edit")
			_editClass();
		else if (input == "cne") {
			_createClass();
			if (!_classes.empty())
				_classes.back()->shellStart();
		}
		else if (input == "export" && !_classes.empty())
			_exportClass(setting);
		else
			std::cout << YLW "Unrecognized input OR no loaded classes, verify using the \'help\' command" CLR << std::endl;
	}
}

void CPP_Constructor::_printHelp() {
	std::cout << BGRN "Here is the list of all possible commands: " CLR << std::endl;
	std::cout << "\thelp: Prints this message" << std::endl;
	std::cout << "\texit: Exits the program" << std::endl;
	std::cout << "\tcreate: Creates a new class" << std::endl;
	std::cout << "\tprint: Prints all the classes" << std::endl;
	std::cout << "\tedit: Edits an class's attributes" << std::endl;
	std::cout << "\tcne: Creates a class and edits the last created class" << std::endl;
	std::cout << "\texport: Exports the loaded classes into .h and .cpp." << std::endl;

	std::cout << std::endl;
}

void CPP_Constructor::_createClass() {
	ClassInfo *newClass = new ClassInfo;
	newClass->setName(userInput("Enter the class's name", userInputBypass));
	for (ulong i = 0; i < _classes.size(); ++i) {
		if (_classes[i]->getName() == newClass->getName())
		{
			std::cerr << BRED "Duplicate class" CLR << std::endl;
			delete newClass;
			return ;
		}
	}
	if (newClass->getName().empty())
	{
		std::cerr << BRED "Empty name" CLR << std::endl;
		delete newClass;
		return ;
	}
	std::cout << "Created class " BOLD << newClass->getName() << CLR << std::endl;
	_classes.push_back(newClass);
}

void CPP_Constructor::_printClasses() {
	AttributeInfo *loop;
	std::cout << "Here is the list of all current classes:" << std::endl;
	for (ulong i = 0; i < _classes.size(); ++i) {
		std::cout << " - " BOLD << _classes[i]->getName() << " ( " CLR;
		loop = _classes[i]->getAttribute().getHead();
		while (loop)
		{
			std::cout << loop->getName() << ", ";
			loop = loop->getNext();
		}
		std::cout << ")" << std::endl;
	}
}

void CPP_Constructor::_editClass() {
	std::string input;

	std::cout << "Valid choices: " << std::endl;
	for (ulong i = 0; i < _classes.size(); ++i) {
		std::cout <<  _classes[i]->getName() << ", " << std::endl;
	}
	input = userInput("Enter the name of the class to edit", userInputBypass);
	for (ulong i = 0; i < _classes.size(); ++i) {
		if (_classes[i]->getName() == input)
		{
			_classes[i]->shellStart();
			return ;
		}
	}
	std::cerr << BRED "Class not found" CLR << std::endl;
}

void CPP_Constructor::_exportClass(Setting setting) {
	std::cout << BCYN "Exporting all loaded classes..." CLR << std::endl;
	std::cout << " ( ";
	for (ClassInfo *loop: _classes) {
		std::cout << loop->getName() << " ";
		_writeH(loop, setting);
		_writeCPP(loop);
	}
	std::cout << ") " << std::endl;

}

void writePublicH(std::ofstream &hpp, ClassInfo *classInfo, Setting setting) {
        (void) classInfo;
        (void) setting;
	hpp << "public:" << std::endl;
}

void writePrivateH(std::ofstream &hpp, ClassInfo *classInfo, Setting setting) {
        if(!classInfo->isProtected())
                hpp << "private:" << std::endl;
        else
                hpp << "protected:" << std::endl;
        if (classInfo->getAttribute().getHead()) {
                AttributeInfo *head = classInfo->getAttribute().getHead();
                while(head != nullptr) {
                        hpp << '\t' << head->getType() << ' ' << setting.prefix << head->getName() << ';' << std::endl;
                        head = head->getNext();
                }
        }
}

void CPP_Constructor::_writeH(ClassInfo *classInfo, Setting setting) {
	std::ofstream hpp;
	std::string uppercase;
	hpp.open(OUTPUT_DIR "/inc/" + classInfo->getName() + ".h", std::ios::trunc);
	if (!hpp.is_open())
	{
		std::cerr << BRED "Couldn't create the file for " << classInfo->getName() << std::endl;
		return;
	}
	uppercase = classInfo->getName();
	for (ulong i = 0; i < uppercase.length(); ++i)
		uppercase[i] = toupper(uppercase[i]);
        if(setting.pragma) {
                hpp << "#pragma once" << std::endl;
        } else {
        	hpp << "#ifndef " << uppercase << "_H" << std::endl;
        	hpp << "# define " << uppercase << "_H" << std::endl;
        }
	hpp << std::endl;
	hpp << "class " << classInfo->getName() << std::endl;
	hpp << "{" << std::endl;
        if(!setting.inverted) {
                writePublicH(hpp, classInfo, setting);
                writePrivateH(hpp, classInfo, setting);
        } else {
                writePrivateH(hpp, classInfo, setting);
                writePublicH(hpp, classInfo, setting);
        }
	hpp << "}" << std::endl;
	hpp << std::endl;
	if(!setting.pragma)
                hpp << "#endif //" << uppercase << std::endl;
	hpp.close();
}

void CPP_Constructor::_writeCPP(ClassInfo *classInfo, Setting setting) {
	(void)classInfo;
}

std::string userInput(const std::string &msg, bool(*check)(std::string)) {
	std::string	input;

	input = "";
	std::cout << BBLU << msg << BLU << std::endl;
	if (check == userInputBypass)
		std::getline(std::cin, input);
	while (check(input))
		std::getline(std::cin, input);
	std::cout << CLR;
	return (input);
}

bool userInputBypass(std::string) {
	return false;
}
