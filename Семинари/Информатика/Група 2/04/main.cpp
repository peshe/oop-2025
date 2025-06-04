#include <iostream>
#include <fstream>

#include "my_string.h"
#include "string_list.h"

int main() {
	StringList sl = createStringList();

	MyString s1 = createString("Hello\n, ");
	MyString s2 = createString("World!");

	std::fstream binFile;
	binFile.open("str.bin", std::ios::out | std::ios::binary);
	serializeString(s1, binFile);
	binFile.close();

	binFile.open("str.bin", std::ios::in | std::ios::binary);
	MyString s3 = deserializeString(binFile);
	std::cout << "--------------" << std::endl;
	printString(s3);
	std::cout << "\n--------------" << std::endl;
	binFile.close();
	deleteString(s3);

	addToStringList(sl, s1);
	addToStringList(sl, s2);

	binFile.open("list.bin", std::ios::out | std::ios::binary);
	serializeStringList(sl, binFile);
	
	addToStringList(sl, s1);
	addToStringList(sl, s2);
	addToStringList(sl, s1);
	addToStringList(sl, s2);
	
	serializeStringList(sl, binFile);
	binFile.close();

	binFile.open("list.bin", std::ios::in | std::ios::binary);
	skipStringList(binFile);
	StringList sl3 = deserializeStringList(binFile);
	binFile.close();
	
	std::cout << "\n***********\n";
	printStringList(sl3);
	std::cout << "\n***********\n";

	deleteStringList(sl3);

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