#ifndef __STRING_LIST_H__
#define __STRING_LIST_H__

#include <fstream>

#include "my_string.h"

class StringList {
private:
	MyString *items = nullptr;
	int size = 0;

	void deleteStringList();

public:
	StringList() = default;
	StringList(std::fstream& file);
	~StringList();

	void print() const;

	// «а упражнение ако искате го направете оператор
	void writeToFile(std::fstream &file) const;

	int serialize(std::fstream& file) const;
	StringList &operator+=(const MyString &s);
};

std::istream &operator>>(std::istream &f, StringList &s);

void skipStringList(std::fstream& file);

#endif // __STRING_LIST_H__