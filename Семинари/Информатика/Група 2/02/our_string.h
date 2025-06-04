#ifndef __OUR_STRING_H__
#define __OUR_STRING_H__

struct MyString {
	char* value;
	size_t size;
};

MyString createString(const char* txt);
void deleteString(MyString& s);

void printString(const MyString& s);
void appendString(MyString& s1, const MyString& s2);

#endif // __OUR_STRING_H__