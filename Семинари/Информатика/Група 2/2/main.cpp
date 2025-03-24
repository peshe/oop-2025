#include <iostream>
#include "our_string.h"
#include "string_list.h"

int main() {
	StringList s;

	MyString s1 = createString("Hello, ");
	MyString s2 = createString("World!");
	
	appendString(s1, s2);

	printString(s1);

	deleteString(s1);
	deleteString(s2);
}