#include "nonemptyString.hpp"

char NonemptyString::moved_from_placeholder[] = "moved from";

NonemptyString::NonemptyString(NonemptyString&& s) noexcept: sz(s.sz), str(s.str)
{
	s.str = moved_from_placeholder;
	s.sz = sizeof(moved_from_placeholder) - 1;
}

NonemptyString::NonemptyString(const char* str, std::size_t sz): sz(sz > 0 ? sz : throw std::invalid_argument("cannot be empty")), str(new char[sz + 1])
{
	std::memcpy(this->str, str, sz);
	this->str[sz] = '\0';
}
NonemptyString::NonemptyString(std::size_t sz, char ch): sz(sz > 0 ? sz : throw std::invalid_argument("cannot be empty")), str(new char[sz + 1])
{
	std::memset(this->str, ch, sz);
	this->str[sz] = '\0';
}

NonemptyString& NonemptyString::operator=(NonemptyString s)
{
	std::swap(str, s.str);
	std::swap(sz, s.sz);
	return *this;
}
NonemptyString::~NonemptyString()
{
	if(str != moved_from_placeholder)
		delete[] str;
}

std::ostream& NonemptyString::print(std::ostream& os) const
{
	return os << sz << '\n' << str << '\n';
}
std::istream& NonemptyString::read(std::istream& is)
{
	std::size_t sz;
	is >> sz;
	NonemptyString tmp(sz, '\0');
	is.read(tmp.str, sz);
	*this = std::move(tmp);
	return is;
}