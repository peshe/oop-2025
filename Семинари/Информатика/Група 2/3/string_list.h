#pragma once

#include <fstream>

#include "my_string.h"

struct StringList {
	MyString *items;
	int size;
};

StringList createStringList();
void addToStringList(StringList &list, const MyString &item);
void deleteStringList(StringList &list);
void printStringList(const StringList &list);
StringList readStringListFromFile(std::fstream& file);
void writeStringListToFile(const StringList& list, std::fstream &file);