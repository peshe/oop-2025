#include "string_list.h"

#include <iostream>

StringList createStringList() {
	StringList res;

	res.items = nullptr;
	res.size = 0;

	return res;
}

void addToStringList(StringList &list, const MyString &item) {
	MyString *newItems = new MyString[list.size + 1];
	
	for (int i = 0; i < list.size; i++) {
		newItems[i] = list.items[i];
	}

	newItems[list.size] = createString(item.value);
	
	delete[] list.items;

	list.items = newItems;
	list.size++;
}

void deleteStringList(StringList &list) {
	for (int i = 0; i < list.size; i++) {
		deleteString(list.items[i]);
	}

	delete[] list.items;
	list.items = nullptr;
	list.size = 0;
}

void printStringList(const StringList &list) {
	for (int i = 0; i < list.size; i++) {
		printString(list.items[i]);
		std::cout << std::endl;
	}
}

void writeStringListToFile(const StringList& list, std::fstream& file) {
	file << list.size << std::endl;
	for (int i = 0; i < list.size; i++) {
		writeMyStringToFile(list.items[i], file);
		file << '\n';
	}
}

StringList readStringListFromFile(std::fstream& file) {
	StringList res = createStringList();

	int size;
	file >> size;

	char buff[1024];
	file.getline(buff, 1023); // За да пропуснем новия ред

	for (int i = 0; i < size; i++) {
		file.getline(buff, 1023);
		MyString s = createString(buff);
		addToStringList(res, s);
		deleteString(s);
	}

	return res;
}