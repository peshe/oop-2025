#ifndef __MY_STRING_H__
#define __MY_STRING_H__

#include <fstream>

struct MyString {
	char* value;
	size_t size;
};

MyString createString(const char* txt);
void deleteString(MyString& s);

void printString(const MyString& s);
void writeMyStringToFile(const MyString& s, std::fstream &file);
void appendString(MyString& s1, const MyString& s2);
int serializeString(const MyString& s, std::fstream &file);
MyString deserializeString(std::fstream& file);

#endif // __MY_STRING_H__