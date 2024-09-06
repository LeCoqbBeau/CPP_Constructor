//
// Created by mscheman on 9/6/24.
//

#ifndef ATTRIBUTELIST_H
#define ATTRIBUTELIST_H

#include "CPP_Constructor.h"
#include "AttributeInfo.h"

class AttributeList {
private:
	AttributeInfo *_head;
public:
	AttributeList();
	~AttributeList();
	void append(AttributeInfo *newAttr);
	void create();
	void remove();
	void remove(const std::string &name);
	void clear();
	AttributeInfo *getHead() const;
};

#endif //ATTRIBUTELIST_H
