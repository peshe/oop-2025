#ifndef __MY_STRING_H__
#define __MY_STRING_H__

#include <fstream>

// Понеже се разбрахме да ходите на други  упражнения следващите два пъти и
// после да си вземем пропуснатите часове като подготовка за контролно, то
// няма да имаме възможност да довършим тези класове. Когато разберете какво са
// конструктори, деструктори и изключения, помислете как можа да ги ползвате
// в този пример. На места имаме проблеми с паметта. Помислете и ги оправете.
//  Може да ми изпратите решенията си за бонус точки.

class MyString {
private:
	char* value = nullptr;
	size_t size = -1;

public:
	size_t getSize() const;
	
	const char* getValue() const;
	void setValue(const char* value);

	void init(const char* txt);
	void deserialize(std::fstream& file);
	void deleteString();
	void print() const;
	void append(const MyString& s2);
	void writeToFile(std::fstream &file) const;
	int serialize(std::fstream &file) const;
};

#endif // __MY_STRING_H__