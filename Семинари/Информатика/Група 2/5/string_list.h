#ifndef __STRING_LIST_H__
#define __STRING_LIST_H__

#include <fstream>

#include "my_string.h"

class StringList {
private:
	MyString *items = nullptr;
	int size = 0;

public:
	void add(const MyString& item);
	void deleteStringList();
	void print() const;
	void writeToFile(std::fstream &file) const;
	void readFromFile(std::fstream& file);
	int serialize(std::fstream& file) const;
	void deserialize(std::fstream& file);
};

void skipStringList(std::fstream& file);

#endif // __STRING_LIST_H__