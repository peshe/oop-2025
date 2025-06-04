#include "string_list.h"

#include <iostream>

StringList::StringList(std::fstream& file) {
	file.seekg(sizeof(int), std::ios::cur);
	file.read((char*)&this->size, sizeof(this->size));
	this->items = new MyString[this->size];
	for (int i = 0; i < this->size; i++) {
		this->items[i] = MyString(file);
	}
}

StringList::~StringList() {
	this->deleteStringList();
}

void StringList::deleteStringList() {
	if (this->items == nullptr) return;

	delete[] this->items;
	this->items = nullptr;
	this->size = 0;
}

void StringList::print() const {
	if (this->size == 0) {
		throw std::exception("Empty string list");
	}

	if (this->size % 2 == 1) {
		// Препоръчително е да хвърляме инстанции на std::exception
		// или на някакви негови наследници (скоро)
		throw "odd size";
	}

	for (int i = 0; i < this->size; i++) {
		this->items[i].print();
		std::cout << std::endl;
	}
}

void StringList::writeToFile(std::fstream& file) const {
	file << this->size << std::endl;
	for (int i = 0; i < this->size; i++) {
		file << this->items[i];
		file << '\n';
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

StringList& StringList::operator+=(const MyString& s) {
	MyString* newItems = new MyString[this->size + 1];

	for (int i = 0; i < this->size; i++) {
		newItems[i] = this->items[i];
	}

	newItems[this->size] = MyString(s.getValue());

	delete[] this->items;

	this->items = newItems;
	this->size++;

	return *this;
}

std::istream &operator>>(std::istream &f, StringList &sl) {
	int size;
	f >> size;

	char buff[1024];
	f.getline(buff, 1023); // За да пропуснем новия ред

	for (int i = 0; i < size; i++) {
		f.getline(buff, 1023);
		MyString s(buff);
		sl += s;
	}

	return f;
}

void skipStringList(std::fstream& file) {
	int size;
	file.read((char*)&size, sizeof(size));
	file.seekg(size, std::ios::cur);
}
