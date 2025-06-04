#include <iostream>
#include <cstring>
#include "my_string.h"

size_t MyString::getSize() const {
	return this->size;
}

const char* MyString::getValue() const {
	return this->value;
}

void MyString::setValue(const char* value) {
	if (this->value != nullptr) {
		this->deleteString();
	}

	this->size = strlen(value);
	this->value = new char[this->size + 1];
	strcpy_s(this->value, this->size + 1, value);
}

void MyString::init(const char* txt) {
	this->setValue(txt);
}

void MyString::deleteString() {
	if (this->value == nullptr) return;
	
	delete[] this->value;
	this->size = -1;
	this->value = nullptr;
}

void MyString::print() const {
	std::cout << this->value;
}

void MyString::append(const MyString& s2) {
	// Тук имаме проблем с паметта ако не сме викнали init за този обект
	// Помислете как да го оправите.

	int newSize = this->size + s2.size;
	char* newValue = new char[newSize + 1];
	
	strcpy_s(newValue, this->size + 1, this->value);
	strcpy_s(newValue + this->size, s2.size + 1, s2.value);

	delete[] this->value;

	this->value = newValue;
	this->size = newSize;
}

void MyString::writeToFile(std::fstream& file) const {
	file << this->value;
}

int MyString::serialize(std::fstream& file) const {
	file.write((char*)&this->size, sizeof(this->size));
	file.write(this->value, this->size);
	return sizeof(this->size) + this->size;
}

void MyString::deserialize(std::fstream& file) {
	if (this->value != nullptr) {
		this->deleteString();
	}

	file.read((char*)&this->size, sizeof(this->size));
	this->value = new char[this->size + 1];
	file.read(this->value, this->size);
	this->value[this->size] = '\0';
}
