//
// Created by mscheman on 9/6/24.
//

#include "AttributeList.h"
#include "macros.h"

AttributeList::AttributeList() {
	this->_head = nullptr;
}

void AttributeList::append(AttributeInfo *newAttr) {
	if (!_head)
	{
		_head = newAttr;
		return ;
	}
	if (!_head->getNext())
	{
		_head->setNext(newAttr);
		return ;
	}
	AttributeInfo *loop = this->_head;
	while (loop->getNext())
	{
		if (loop->getNext()->getName() == newAttr->getName())
		{
			delete newAttr;
			std::cerr << BRED "Duplicate attribute";
			return ;
		}
		loop = loop->getNext();
	}
	loop->setNext(newAttr);
}

void AttributeList::create() {
	AttributeInfo *created = new AttributeInfo();
	created->setNext(nullptr);
	created->setType(userInput("Please enter the attribute's type", userInputBypass));
	created->setName(userInput("Please enter the attribute's name", userInputBypass));
	append(created);
}

void AttributeList::remove() {
	if (!_head->getNext())
	{
		delete this->_head;
		this->_head = nullptr;
		return ;
	}
	AttributeInfo *loop = this->_head;
	while (loop->getNext()->getNext())
		loop = loop->getNext();
	delete loop->getNext();
	loop->setNext(nullptr);
}

void AttributeList::remove(const std::string &name) {
	AttributeInfo *loop = this->_head;
	while (loop)
	{
		if (loop->getNext()->getName() == name)
			break;
		loop = loop->getNext();
	}
	if (!loop)
		return ;
	AttributeInfo *del = loop->getNext();
	loop->setNext(del->getNext());
	delete del;
}

void AttributeList::clear() {
	while (_head)
		remove();
}

AttributeList::~AttributeList() {
	clear();
}

AttributeInfo *AttributeList::getHead() const {
	return _head;
}
