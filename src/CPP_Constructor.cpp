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
			_createClass(&setting);
		else if (input == "print")
			_printClasses();
		else if (input == "edit")
			_editClass();
		else if (input == "cne") {
			_createClass(&setting);
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

void CPP_Constructor::_createClass(Setting *setting) {
	ClassInfo *newClass = new ClassInfo(setting);

	newClass->setName(userInput("Enter the class's name", userInputBypass));
	{
		std::string classname;
		std::string camelcase;
		classname = newClass->getName();
		camelcase += toupper(classname[0]);
		for (ulong i = 1; i < classname.length(); ++i) {
			if (classname[i] == '_')
			{
				i++;
				camelcase += toupper(classname[i]);
			}
			else
				camelcase += tolower(classname[i]);
		}
		newClass->setName(camelcase);
	} // Puts the class name in camel casing

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
		_writeCPP(loop, setting);
	}
	std::cout << ") " << std::endl;
}

static std::string toCamelCase(const std::string &str)
{
	std::string	ret;
	int i = 0;
	while (!isalnum(str[i++]));
	ret += toupper(str[i - 1]);
	while (str[i])
	{
		if (isspace(str[i]) || str[i] == '_')
		{
			while (isspace(str[i++]));
			ret += toupper(str[i]);
		}
		else
			ret += tolower(str[i]);
		i++;
	}
	return ret;
}

static std::string toSnakeCase(const std::string &str)
{
	std::string	ret;
	int i = 0;
	while (!isalnum(str[i++]));
	ret += tolower(str[i - 1]);
	while (str[i])
	{
		if (isupper(str[i]))
			ret += '_';
		ret += tolower(str[i]);
		i++;
	}
	return ret;
}

static void writePublicH(std::ofstream &h, ClassInfo *classInfo, Setting setting) {
	AttributeInfo *loop;
	(void)setting;

	h << "public:" << std::endl;

	h << "\t// Orthodox Canonical Form" << std::endl;
	h << "\t" << classInfo->getName() << "();" << std::endl;
	{
		loop = classInfo->getAttribute().getHead();
                if(loop) {
		        h << "\t" << classInfo->getName() << "(";
		        while (loop && loop->getNext())
		        {
		        	h << "const " << loop->getType() << " &" << loop->getName() << ", ";
		        	loop = loop->getNext();
		        }
		        h << "const " << loop->getType() << " &" << loop->getName();
		        h << ");" << std::endl;
                }
	}
	h << "\t" << classInfo->getName() << "(const " << classInfo->getName() << " &src);" << std::endl;
	h << "\t" << classInfo->getName() << "&operator=(const " << classInfo->getName() << " &rhs);" << std::endl;
	h << "\t~" << classInfo->getName() << "();" << std::endl;

	h << std::endl;

	h << "\t// Accessors" << std::endl;
	{
		std::string camelCased;
		loop = classInfo->getAttribute().getHead();
		while (loop)
		{
			camelCased = toCamelCase(loop->getName());
			h << "\t" << loop->getType() << " &get" << camelCased << "();" << std::endl;
			h << "\t" << "void set" << camelCased << "(const " << loop->getType() << " &" << camelCased << ");" << std::endl;
			loop = loop->getNext();
		}
	}

	h << std::endl;
}

static void writePrivateH(std::ofstream &h, ClassInfo *classInfo, Setting setting) {
	if(!classInfo->isProtected())
		h << "private:" << std::endl;
	else
		h << "protected:" << std::endl;
	if (!classInfo->getAttribute().getHead())
		return;
	AttributeInfo *head = classInfo->getAttribute().getHead();
	std::string snake_cased;
	while(head != nullptr) {
		snake_cased = toSnakeCase(head->getName());
		h << '\t' << head->getType() << ' ' << setting.prefix << snake_cased << ';' << std::endl;
		head = head->getNext();
	}
}

void CPP_Constructor::_writeH(ClassInfo *classInfo, Setting setting) {
	std::ofstream h;
	std::string uppercase;
	h.open(OUTPUT_DIR "/inc/" + classInfo->getName() + ".h", std::ios::trunc);
	if (!h.is_open())
	{
		std::cerr << BRED "Couldn't create the file for " << classInfo->getName() << std::endl;
		return;
	}
	uppercase = classInfo->getName();
	for (ulong i = 0; i < uppercase.length(); ++i)
		uppercase[i] = toupper(uppercase[i]);
	if(setting.pragma) {
			h << "#pragma once" << std::endl;
	} else {
		h << "#ifndef " << uppercase << "_H" << std::endl;
		h << "# define " << uppercase << "_H" << std::endl;
	}
	if (setting.lib) {
		h << std::endl;
		h << "# include <iostream>" << std::endl;
		h << "# include <string>" << std::endl;
	}
        std::vector<Includes> &incs = classInfo->getIncludes();
        if(!incs.empty() && !setting.lib) h << std::endl;
        for(auto inc : incs) {
                if(!inc.local) h << "# include <" << inc.name << ">" << std::endl;
                else h << "# include \"" << inc.name << "\"" << std::endl;
        }
	if (setting.color)
		h << "# include \"colors.h\"" << std::endl;
	h << std::endl;
	h << "class " << classInfo->getName() << std::endl;
	h << "{" << std::endl;
	if(!setting.inverted) {
		writePublicH(h, classInfo, setting);
		writePrivateH(h, classInfo, setting);
	} else {
		writePrivateH(h, classInfo, setting);
		writePublicH(h, classInfo, setting);
	}
	h << "}" << std::endl;
	h << std::endl;
	if(!setting.pragma)
		h << "#endif //" << uppercase << std::endl;
	h.close();
}

void CPP_Constructor::_writeCPP(ClassInfo *classInfo, Setting setting) {
	std::ofstream cpp;
	AttributeInfo	*loop;

	cpp.open(OUTPUT_DIR "/src/" + classInfo->getName() + ".cpp", std::ios::trunc);
	if (!cpp.is_open())
	{
		std::cerr << BRED "Couldn't create the file for " << classInfo->getName() << std::endl;
		return;
	}
	cpp << "#include \"" << classInfo->getName() << ".h\"" << std::endl;
	cpp << std::endl;
	{
		cpp << classInfo->getName() << "::" << classInfo->getName() << "() {" << std::endl;
		if (setting.announcer)
		{
			cpp << "\tstd::cout << ";
			if (setting.color)
				cpp << "BGRN ";
			cpp << '"' << classInfo->getName() << " Default Constructor called\"";
			if (setting.color)
				cpp << " CLR";
			cpp << ";" << std::endl;

			cpp << "\tstd::cout << ";
			if (setting.color)
				cpp << "BBLK ";
			cpp << "\" [ \" << &this << \" ] \"";
			if (setting.color)
				cpp << " CLR";
			cpp << " << std::endl;" << std::endl;
		}
		cpp << "}" << std::endl;
	}
	cpp << std::endl;
	do {
		loop = classInfo->getAttribute().getHead();
		if (!loop)
			break;
		cpp << classInfo->getName() << "::" << classInfo->getName() << "(";
		while (loop->getNext())
		{
			cpp << "const " << loop->getType() << " &" << loop->getName() << ", ";
			loop = loop->getNext();
		}
		cpp << "const " << loop->getType() << " &" << loop->getName();
		cpp << ") {" << std::endl;
		if (setting.announcer)
		{
			cpp << "\tstd::cout << ";
			if (setting.color)
				cpp << "BGRN ";
			cpp << '"' << classInfo->getName() << " Parameterized Constructor called\"";
			if (setting.color)
				cpp << " CLR";
			cpp << ";" << std::endl;

			cpp << "\tstd::cout << ";
			if (setting.color)
				cpp << "BBLK ";
			cpp << "\" [ \" << &this << \" ] \"";
			if (setting.color)
				cpp << " CLR";
			cpp << " << std::endl;" << std::endl;
		}
		loop = classInfo->getAttribute().getHead();
		while (loop)
		{
			cpp << "\tthis->" << setting.prefix + loop->getName() << " = " << loop->getName() << ";" << std::endl;
			loop = loop->getNext();
		}
		cpp << "}" << std::endl;
	} while(false);
	cpp << std::endl;
	{
		cpp << classInfo->getName() << "::" << classInfo->getName() << "(";
		cpp << "const " << classInfo->getName() << " &src) {" << std::endl;
		if (setting.announcer)
		{
			cpp << "\tstd::cout << ";
			if (setting.color)
				cpp << "BGRN ";
			cpp << '"' << classInfo->getName() << " Copy Constructor called\"";
			if (setting.color)
				cpp << " CLR";
			cpp << ";" << std::endl;

			cpp << "\tstd::cout << ";
			if (setting.color)
				cpp << "BBLK ";
			cpp << "\" [ from \" << &rhs << to << &this << \" ] \"";
			if (setting.color)
				cpp << " CLR";
			cpp << " << std::endl;" << std::endl;
		}
		loop = classInfo->getAttribute().getHead();
		while (loop)
		{
			cpp << "\tthis->" << setting.prefix << loop->getName() << " = src." << setting.prefix << loop->getName() << ";" << std::endl;
			loop = loop->getNext();
		}
		cpp << "}" << std::endl;
	}
	cpp << std::endl;
	{
		cpp << classInfo->getName() << " &" << classInfo->getName() << "::operator=(const " << classInfo->getName() << " &rhs) {" << std::endl;
		if (setting.announcer)
		{
			cpp << "\tstd::cout << ";
			if (setting.color)
				cpp << "BGRN ";
			cpp << '"' << classInfo->getName() << " Assignment Operator called\"";
			if (setting.color)
				cpp << " CLR";
			cpp << ";" << std::endl;

			cpp << "\tstd::cout << ";
			if (setting.color)
				cpp << "BBLK ";
			cpp << "\" [ from \" << &rhs << to << &this << \" ] \"";
			if (setting.color)
				cpp << " CLR";
			cpp << " << std::endl;" << std::endl;
		}
		loop = classInfo->getAttribute().getHead();
		while (loop)
		{
			cpp << "\tthis->" << setting.prefix << loop->getName() << " = rhs." << setting.prefix << loop->getName() << ";" << std::endl;
			loop = loop->getNext();
		}
		cpp << "\treturn *this;" << std::endl;
		cpp << "}" << std::endl;
	}
	cpp << std::endl;
	{
		cpp << classInfo->getName() << "::~" << classInfo->getName() << "() {" << std::endl;
		if (setting.announcer)
		{
			cpp << "\tstd::cout << ";
			if (setting.color)
				cpp << "BGRN ";
			cpp << '"' << classInfo->getName() << " Destructor called\"";
			if (setting.color)
				cpp << " CLR";
			cpp << ";" << std::endl;

			cpp << "\tstd::cout << ";
			if (setting.color)
				cpp << "BBLK ";
			cpp << "\" [ \" << &this << \" ] \"";
			if (setting.color)
				cpp << " CLR";
			cpp << " << std::endl;" << std::endl;
		}
		cpp << "}" << std::endl;
	}
	cpp << std::endl;
	cpp.close();
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
