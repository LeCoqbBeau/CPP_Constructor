//
// Created by mscheman on 9/6/24.
//

#include "ClassInfo.h"
#include "macros.h"

ClassInfo::ClassInfo(Setting *setting) {
        _setting = setting;
	_protected = false;
}

const std::string &ClassInfo::getName() const {
	return _name;
}

void ClassInfo::setName(const std::string &name) {
	_name = name;
}

AttributeList& ClassInfo::getAttribute() {
	return _attributes;
}

void ClassInfo::shellStart() {
	std::string input;

	std::cout << std::endl;
	std::cout << BCYN "Editing Class: " CLR BOLD << _name << CLR << std::endl;
	std::cout << std::endl;
	_printHelp();
	while (!std::cin.eof())
	{
		std::cout << " " << _name << " > ";
		std::getline(std::cin, input);
		if (input == "help")
			_printHelp();
		else if (input == "exit")
			break ;
		else if (input == "add")
			getAttribute().create();
		else if (input == "print")
			_printAttr();
		else if (input == "edit")
			_editAttr();
		else if (input == "prot")
			_protected = true;
                else if (input == "include")
                        _addInclude();
		else
			std::cout << YLW "Unrecognized input, verify using the \'help\' command" CLR << std::endl;
	}
}

void ClassInfo::_addInclude() {
        std::string input = userInput("Enter the file to include", userInputBypass);
        _includes.push_back(input);
}

void ClassInfo::_printHelp() {
	std::cout << BGRN "Here is the list of all possible commands: " CLR << std::endl;
	std::cout << "\thelp: Prints this message" << std::endl;
	std::cout << "\texit: Exit the Class editing" << std::endl;
	std::cout << "\tadd: Adds an new attribute" << std::endl;
	std::cout << "\tprint: Prints the class's attribute(s)" << std::endl;
	std::cout << "\tedit: Edits an attribute's name or type" << std::endl;
        std::cout << "\tprot: Set class to use protected instead of private" << std::endl;
        std::cout << "\tinclude: add include in the class header" << std::endl;
	std::cout << std::endl;
}

std::vector<std::string> &ClassInfo::getIncludes() {
        return _includes;
}

bool ClassInfo::isProtected() {
        return _protected;
}

void ClassInfo::_printAttr() {
	AttributeInfo *loop = getAttribute().getHead();
	std::cout << "Class: " BOLD << _name << CLR << std::endl;
	while (loop)
	{
		std::cout << "\t" << loop->getType() << " " << _setting->prefix << loop->getName() << std::endl;
		loop = loop->getNext();
	}
	std::cout << std::endl;
}

static bool isTypeOrName(std::string input)
{
	if (input == "T")
		return false;
	if (input == "N")
		return false;
	return true;
}

void ClassInfo::_editAttr() {
	AttributeInfo *loop = getAttribute().getHead();
	std::string input;
	_printAttr();
	input = userInput("Enter the name (without the prefix \"" + _setting->prefix + "\") of the attribute to edit", userInputBypass);
	while (loop) {
		if (loop->getName() == input)
			break;
		loop = loop->getNext();
	}
	if (!loop)
	{
		std::cerr << BRED "Attribute not found" CLR << std::endl;
		return ;
	}
	input = userInput("Modify the (N)ame or the (T)ype", isTypeOrName);
	if (input == "N")
		loop->setName(userInput("Enter the new name", userInputBypass));
	else
		loop->setType(userInput("Enter the new type", userInputBypass));
}
