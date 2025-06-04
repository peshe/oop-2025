#include "string_list.h"

#include <iostream>

void StringList::add(const MyString &item) {
	MyString *newItems = new MyString[this->size + 1];
	
	for (int i = 0; i < this->size; i++) {
		newItems[i] = this->items[i];
	}

	newItems[this->size].init(item.getValue());
	
	delete[] this->items;

	this->items = newItems;
	this->size++;
}

void StringList::deleteStringList() {
	if (this->items == nullptr) return;

	for (int i = 0; i < this->size; i++) {
		this->items[i].deleteString();
	}

	delete[] this->items;
	this->items = nullptr;
	this->size = 0;
}

void StringList::print() const {
	for (int i = 0; i < this->size; i++) {
		this->items[i].print();
		std::cout << std::endl;
	}
}

void StringList::writeToFile(std::fstream& file) const {
	file << this->size << std::endl;
	for (int i = 0; i < this->size; i++) {
		this->items[i].writeToFile(file);
		file << '\n';
	}
}

void StringList::readFromFile(std::fstream& file) {
	int size;
	file >> size;

	char buff[1024];
	file.getline(buff, 1023); // За да пропуснем новия ред

	for (int i = 0; i < size; i++) {
		file.getline(buff, 1023);
		MyString s;
		s.init(buff);
		this->add(s);
		s.deleteString();
	}
}

int StringList::serialize(std::fstream& file) const {
	int size = sizeof(this->size);

	int writePointer = file.tellp();
	file.write((char*)&size, sizeof(size));
	file.write((char*)&this->size, sizeof(this->size));

	for (int i = 0; i < this->size; i++) {
		size += this->items[i].serialize(file);
	}

	file.seekp(writePointer);
	file.write((char*)&size, sizeof(size));
	file.seekp(size, std::ios::cur);
	return size;
}

void StringList::deserialize(std::fstream& file) {
	file.seekg(sizeof(int), std::ios::cur);
	file.read((char*)&this->size, sizeof(this->size));
	this->items = new MyString[this->size];
	for (int i = 0; i < this->size; i++) {
		this->items[i].deserialize(file);
	}
}

void skipStringList(std::fstream& file) {
	int size;
	file.read((char*)&size, sizeof(size));
	file.seekg(size, std::ios::cur);
}