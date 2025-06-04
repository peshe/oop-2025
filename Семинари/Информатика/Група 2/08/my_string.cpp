#include <iostream>
#include <cstring>
#include "my_string.h"

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
	// �� � �����, �� ��������� ���� �� �� ��������,
	// �� �� ��� ��-������� �� ���� ������� � �������
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

std::ostream& operator<<(std::ostream& f, const MyString& s) {
	f << s.value;

	return f;
}