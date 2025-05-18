#pragma once

#include <cstring>
#include <stdexcept>
#include <iostream>

class NonemptyString
{
	std::size_t sz;
	char* str;
	static char moved_from_placeholder[];
public:
	NonemptyString(const char* str): NonemptyString(str, std::strlen(str)) {}
	NonemptyString(const char* str, std::size_t sz);
	NonemptyString(std::size_t sz, char ch);
	NonemptyString(const NonemptyString& s): NonemptyString(s.str, s.sz) {}
	NonemptyString(NonemptyString&& s) noexcept;
	NonemptyString& operator=(NonemptyString s);
	~NonemptyString();

	std::ostream& print(std::ostream& os) const;
	std::istream& read(std::istream& is);

	const char* c_str() const { return str; }
};

bool operator==(const NonemptyString& lhs, const NonemptyString& rhs);