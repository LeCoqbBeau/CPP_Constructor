//
// Created by mscheman on 9/6/24.
//

#ifndef ATTRIBUTEINFO_H
#define ATTRIBUTEINFO_H

#include <string>

class AttributeInfo {
private:
	std::string		_name;
	std::string		_type;
	AttributeInfo	*_next;
public:
	AttributeInfo();
	const std::string &getName() const;
	void setName(const std::string &name);
	const std::string &getType() const;
	void setType(const std::string &type);
	AttributeInfo *getNext() const;
	void setNext(AttributeInfo *next);
};

#endif //ATTRIBUTEINFO_H
