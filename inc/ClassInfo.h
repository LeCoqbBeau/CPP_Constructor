//
// Created by mscheman on 9/6/24.
//

#ifndef CLASSINFO_H
#define CLASSINFO_H

#include <string>
#include <typeinfo>
#include <vector>
#include "AttributeList.h"
#include "options.h"

class ClassInfo {
	private:
		std::string _name;
		bool _protected;
		AttributeList _attributes;
                std::vector<std::string> _includes;
                Setting *_setting;
		void _printHelp();
		void _editAttr();
		void _printAttr();
                void _addInclude();
	public:
		ClassInfo(Setting *setting);
		const std::string &getName() const;
		void setName(const std::string &name);
		bool isProtected();
		AttributeList &getAttribute();
                std::vector<std::string> &getIncludes();
		void shellStart();
};


#endif //CLASSINFO_H
