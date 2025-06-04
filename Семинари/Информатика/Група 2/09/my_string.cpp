#include <iostream>
#include <cstring>
#include "my_string.h"

MyString::MyString(char *value, size_t size) {
	this->value = value;
	this->size = size;
}

MyString::MyString(std::fstream& file) {
	file.read((char*)&this->size, sizeof(this->size));
	this->value = new char[this->size + 1];
	file.read(this->value, this->size);
	this->value[this->size] = '\0';
}

MyString::MyString(const char* txt) {
	this->setValue(txt);
}

MyString::MyString(const MyString& o) {
	this->setValue(o.value);
}

MyString::~MyString() {
	this->deleteString();
}

size_t MyString::getSize() const {
	return this->size;
}

const char* MyString::getValue() const {
	return this->value;
}

void MyString::setValue(const char* value) {
	this->size = strlen(value);
	this->value = new char[this->size + 1];
	strcpy_s(this->value, this->size + 1, value);
}


void MyString::deleteString() {
	// Не е нужно, но котролнот може да го оставите,
	// за да сте по-сигурни че няма проблем с паметта
	if (this->value == nullptr) return;
	
	delete[] this->value;
	this->size = -1;
	this->value = nullptr;
}

void MyString::print() const {
	std::cout << this->value;
}

void MyString::append(const MyString& s2) {
	int newSize = this->size + s2.size;
	char* newValue = new char[newSize + 1];
	
	strcpy_s(newValue, this->size + 1, this->value);
	strcpy_s(newValue + this->size, s2.size + 1, s2.value);

	delete[] this->value;

	this->value = newValue;
	this->size = newSize;
}

int MyString::serialize(std::fstream& file) const {
	file.write((char*)&this->size, sizeof(this->size));
	file.write(this->value, this->size);
	return sizeof(this->size) + this->size;
}

MyString& MyString::operator=(const char* txt) {
	this->deleteString();
	this->setValue(txt);

	return *this;
}

MyString& MyString::operator=(const MyString& o) {
	this->deleteString();
	this->setValue(o.value);

	return *this;
}

MyString MyString::operator+(const MyString &o) const {
	int newSize = this->size + o.size;
	char* newTxt = new char[newSize + 1];
	
	strcpy_s(newTxt, newSize + 1, this->value);
	strcat_s(newTxt, newSize + 1, o.value);

	return MyString(newTxt, newSize);
}

MyString operator*(const MyString &s, unsigned n) {
	//MyString res;

	//for (unsigned i = 0; i < n; i++) {
	//	res = res + s;
	//}

	//return res;

	int newSize = s.size * n;
	char* newText = new char[newSize + 1];
	strcpy_s(newText, newSize + 1, s.value);

	for (unsigned i = 1; i < n; i++) {
		strcat_s(newText, newSize + 1, s.value);
	}

	return MyString(newText, newSize);
}

std::ostream& operator<<(std::ostream& f, const MyString& s) {
	f << s.value;

	return f;
}