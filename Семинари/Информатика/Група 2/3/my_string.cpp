#include <iostream>
#include <cstring>
#include "my_string.h"

MyString createString(const char* txt) {
	MyString result;

	result.size = strlen(txt);
	result.value = new char[result.size + 1];
	strcpy_s(result.value, result.size + 1, txt);

	return result;
}

void deleteString(MyString& s) {
	delete[] s.value;
	s.size = 0;
	s.value = nullptr;
}

void printString(const MyString& s) {
	std::cout << s.value;
}

void appendString(MyString& s1, const MyString& s2) {
	int newSize = s1.size + s2.size;
	char* newValue = new char[newSize + 1];
	
	strcpy_s(newValue, s1.size + 1, s1.value);
	strcpy_s(newValue + s1.size, s2.size + 1, s2.value);

	delete[] s1.value;

	s1.value = newValue;
	s1.size = newSize;
}

void writeMyStringToFile(const MyString& s, std::fstream& file) {
	file << s.value;
}