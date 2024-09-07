//
// Created by mscheman on 8/16/24.
//

#include "CPP_Constructor.h"
#include "options.h"
#include <ios>

int	main(int count, char *args[])
{
        Setting setting;
        try {
                setting = getopts(count - 1, args + 1);
        } catch(std::exception &e) {
                usage(args[0]);
                std::cerr << "[ERROR] => " << e.what() << std::endl;
                return 1;
        }
        std::cout << std::boolalpha << setting.pragma << std::endl;
	CPP_Constructor cppConstructor;

	cppConstructor.createOutputDir();
	cppConstructor.shellStart(setting);
        return 0;
}
