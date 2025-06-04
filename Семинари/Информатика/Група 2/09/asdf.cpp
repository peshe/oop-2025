#include <iostream>
#include <fstream>

#include "my_string.h"
#include "string_list.h"
#include "worker.h"

int main() {

	MyString a("asdf");
	MyString b("qwer");
	
	MyString c = a + b * 3;

	c.print();
	std::cout << std::endl;

	return 0;
	//////////////////////////////////////////////////////////////////

	StringList sl;
	try {
		sl.print();
	} 
	catch (std::exception &e) {
		std::cout << "Error: " << e.what() << std::endl;
		//return 1;
	}
	catch (const char* e) {
		std::cout << "Error 2: " << e << std::endl;
	}

	MyString s1("Hello\n, ");
	MyString s2("World!");

	s2 = "asdf";

	std::fstream binFile;
	binFile.open("str.bin", std::ios::out | std::ios::binary);
	s1.serialize(binFile);
	binFile.close();

	binFile.open("str.bin", std::ios::in | std::ios::binary);
	MyString s3(binFile);
	std::cout << "--------------" << std::endl;
	s3.print();
	std::cout << "\n--------------" << std::endl;
	binFile.close();

	sl += s1;
	sl += s2;

	binFile.open("list.bin", std::ios::out | std::ios::binary);
	sl.serialize(binFile);
	
	sl += s1;
	sl += s2;
	sl += s1;
	sl += s2;
	
	sl.serialize(binFile);
	binFile.close();

	binFile.open("list.bin", std::ios::in | std::ios::binary);
	skipStringList(binFile);
	StringList sl3(binFile);
	binFile.close();
	
	std::cout << "\n***********\n";
	sl3.print();
	std::cout << "\n***********\n";

	std::fstream file;
	file.open("list.txt", std::ios::out | std::ios::trunc);

	sl.writeToFile(file);

	file.close();

	file.open("list.txt", std::ios::in);
	StringList sl2;
	file >> sl2;

	sl2.print();
}