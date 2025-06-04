#include <iostream>
#include <fstream>

#include "my_string.h"
#include "string_list.h"

int main() {
	StringList sl;

	MyString s1;
	s1.init("Hello\n, ");
	s1.init("asdfg\n, ");
	MyString s2;
	s2.init("World!");

	std::fstream binFile;
	binFile.open("str.bin", std::ios::out | std::ios::binary);
	s1.serialize(binFile);
	binFile.close();

	binFile.open("str.bin", std::ios::in | std::ios::binary);
	MyString s3;
	s3.deserialize(binFile);
	std::cout << "--------------" << std::endl;
	s3.print();
	std::cout << "\n--------------" << std::endl;
	binFile.close();
	s3.deleteString();

	sl.add(s1);
	sl.add(s2);

	binFile.open("list.bin", std::ios::out | std::ios::binary);
	sl.serialize(binFile);
	
	sl.add(s1);
	sl.add(s2);
	sl.add(s1);
	sl.add(s2);
	
	sl.serialize(binFile);
	binFile.close();

	binFile.open("list.bin", std::ios::in | std::ios::binary);
	skipStringList(binFile);
	StringList sl3;
	sl3.deserialize(binFile);
	binFile.close();
	
	std::cout << "\n***********\n";
	sl3.print();
	std::cout << "\n***********\n";

	sl3.deleteStringList();

	std::fstream file;
	file.open("list.txt", std::ios::out | std::ios::trunc);

	sl.writeToFile(file);

	file.close();

	file.open("list.txt", std::ios::in);
	StringList sl2;
	sl2.readFromFile(file);

	sl2.print();

	sl2.deleteStringList();
	sl.deleteStringList();

	s1.deleteString();
	s2.deleteString();
}