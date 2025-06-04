#ifndef __MY_STRING_H__
#define __MY_STRING_H__

#include <fstream>

class MyString {
private:
	char* value = nullptr;
	size_t size = -1;
	void deleteString();
	void setValue(const char* value);

	friend std::ostream& operator<<(std::ostream& f, const MyString& s);

public:
	MyString(const char* txt = "");
	MyString(std::fstream& file);
	MyString(const MyString &o);
	~MyString();

	size_t getSize() const;
	
	const char* getValue() const;

	void print() const;
	void append(const MyString& s2); // Ако искате за упражнение го направете с +=
	int serialize(std::fstream &file) const;
	
	MyString &operator=(const char* txt);
	MyString &operator=(const MyString &o);
};

std::ostream& operator<<(std::ostream &f, const MyString &s);


#endif // __MY_STRING_H__