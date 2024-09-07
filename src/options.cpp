//
// Created by tdelage on 9/7/24.
//

#include <cctype>
#include <stdexcept>
#include <exception>
#include <iostream>
#include "options.h"

namespace std {
	template <typename _CharT, typename _Traits>
	inline basic_ostream<_CharT, _Traits> &tab(basic_ostream<_CharT, _Traits> &__os) {
		return __os << '\t';
	}
}

bool isValidPrefix(std::string prefix) {
	if(!(std::isalpha(prefix[0]) || prefix[0] == '_')) return false;
	for(auto c : prefix) if(!(std::isalnum(c) || c == '_')) return false;
	return true;
}

Setting getopts(int count, char *args[]) {
	Setting ret = {
		.inverted = false,
		.pragma = false,
		.lib = false,
		.color = false,
		.announcer = false,
		.prefix = "_",
	};
	if(count == 0) goto end;
	for(int i = 0; i < count; i++) {
		std::string arg = args[i];
		if (arg == "-i" || arg == "--invert") {
			ret.inverted = !ret.inverted;
		} else if (arg == "-p" || arg == "--prefix") {
			i++;
			if(count - i < 1)
				throw std::logic_error("missing argument for " + arg + " argument");
			std::string prefix = args[i];
			if(!isValidPrefix(prefix))
				throw std::logic_error("prefix should be define as this regex : [a-zA-Z_]([a-zA-Z0-9_])*");
			ret.prefix = prefix;
		} else if (arg == "-d" || arg == "--pragma") {
			ret.pragma = !ret.pragma;
		} else if (arg == "-l" || arg == "--lib") {
			ret.lib = !ret.lib;
		} else if (arg == "-c" || arg == "--color") {
			ret.color = !ret.color;
		} else if (arg == "-a" || arg == "--announce") {
			ret.announcer = !ret.announcer;
		} else {
			throw std::logic_error("unknown argument : " + arg);
		}
	}
end:
	return ret;
}

void usage(char *program) {
	std::cerr << "Usage : " << program << " [OPTIONS]" << std::endl;
	std::cerr << std::tab << "-i          | --invert          : will write private/protected attributes first in header files" << std::endl;
	std::cerr << std::tab << "-p <prefix> | --prefix <prefix> : set custom prefix for variable names" << std::endl;
	std::cerr << std::tab << "-d          | --pragma          : set header protection to use pragma instead of ifndef" << std::endl;
	std::cerr << std::tab << "-l          | --lib             : add common CPP libraries into all headers" << std ::endl;
	std::cerr << std::tab << "-c          | --color           : exports an color library, and makes '-a' statements colored" << std ::endl;
	std::cerr << std::tab << "-a          | --announce        : add announcement statement to constructors, operators, and destructor" << std ::endl;
}
