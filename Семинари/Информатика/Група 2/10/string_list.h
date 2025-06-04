#ifndef __STRING_LIST_H__
#define __STRING_LIST_H__

#include <fstream>

#include "my_string.h"

class StringList {
public:
	class Iterator {
	private:
		Iterator(StringList* l);
		friend class StringList;

		StringList *list;
		int current = 0;

	public:
		bool hasElement() const;
		void next();
		MyString *get() const;

		MyString *operator*();
		MyString *operator->();
		void operator++();
		void operator++(int);
		operator bool();
	};

private:
	MyString *items = nullptr;
	int size = 0;

	void deleteStringList();

public:
	StringList() = default;
	StringList(std::fstream& file);
	~StringList();

	Iterator begin();

	void print() const;

	// За упражнение ако искате го направете оператор
	void writeToFile(std::fstream &file) const;

	int serialize(std::fstream& file) const;
	StringList &operator+=(const MyString &s);
};

std::istream &operator>>(std::istream &f, StringList &s);

void skipStringList(std::fstream& file);

#endif // __STRING_LIST_H__

