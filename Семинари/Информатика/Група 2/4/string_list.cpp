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

int serializeStringList(const StringList& sl, std::fstream& file) {
	int size = sizeof(sl.size);

	int writePointer = file.tellp();
	file.write((char*)&size, sizeof(size));
	file.write((char*)&sl.size, sizeof(sl.size));

	for (int i = 0; i < sl.size; i++) {
		size += serializeString(sl.items[i], file);
	}

	file.seekp(writePointer);
	file.write((char*)&size, sizeof(size));
	file.seekp(size, std::ios::cur);
	return size;
}

StringList deserializeStringList(std::fstream& file) {
	StringList res;

	file.seekg(sizeof(int), std::ios::cur);
	file.read((char*)&res.size, sizeof(res.size));
	res.items = new MyString[res.size];
	for (int i = 0; i < res.size; i++) {
		res.items[i] = deserializeString(file);
	}

	return res;
}

void skipStringList(std::fstream& file) {
	int size;
	file.read((char*)&size, sizeof(size));
	file.seekg(size, std::ios::cur);
}