//
// Created by mscheman on 9/6/24.
//

#include "AttributeInfo.h"

AttributeInfo::AttributeInfo() {
	_next = nullptr;
}

const std::string &AttributeInfo::getName() const {
	return _name;
}

void AttributeInfo::setName(const std::string &name) {
	_name = name;
}

const std::string &AttributeInfo::getType() const {
	return _type;
}

void AttributeInfo::setType(const std::string &type) {
	_type = type;
}

AttributeInfo *AttributeInfo::getNext() const {
	return _next;
}

void AttributeInfo::setNext(AttributeInfo *next) {
	AttributeInfo::_next = next;
}
