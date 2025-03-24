#include <iostream>
#include <fstream>

#include "my_string.h"
#include "string_list.h"

int main() {
	StringList sl = createStringList();

	MyString s1 = createString("Hello, ");
	MyString s2 = createString("World!");

	addToStringList(sl, s1);
	addToStringList(sl, s2);
	addToStringList(sl, s1);
	addToStringList(sl, s2);
	addToStringList(sl, s1);
	addToStringList(sl, s2);

	std::fstream file;
	file.open("list.txt", std::ios::out | std::ios::trunc);

	writeStringListToFile(sl, file);

	file.close();

	file.open("list.txt", std::ios::in);
	StringList sl2 = readStringListFromFile(file);

	printStringList(sl2);

	deleteStringList(sl2);
	deleteStringList(sl);

	deleteString(s1);
	deleteString(s2);
}