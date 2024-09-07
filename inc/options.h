//
// Created by tdelage on 9/7/24.
//

#ifndef OPTIONS_H
#define OPTIONS_H

#include <string>

struct Setting {
       bool inverted; 
       bool pragma;
	   bool	lib;
	   bool color;
	   bool announcer;
       std::string prefix;
};

Setting getopts(int count, char *args[]);
void usage(char *program);

#endif //OPTIONS_H
