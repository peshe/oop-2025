#include "Date.hpp"
#include <stdexcept>

const int MAX_DAYS_MONTH[] = { 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

bool isLeapYear(unsigned int year) {
	return ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0);
}

bool isDigit(char ch) {
	return ch >= '0' && ch <= '9';
}

Date::Date(unsigned day, unsigned month, unsigned year) 
	: day(0), month(0), year(0)
{
	this->setDay(day);
	this->setMonth(month);
	this->setYear(year);
}

Date::Date(const char* dateString) 
	: day(0), month(0), year(0)
{
	if (!dateString || std::strlen(dateString) != 10) {
		throw std::invalid_argument("Invalid date string");
	}

	std::size_t stringIndex = 0;
	unsigned int day = 0, month = 0, year = 0;

	while (dateString[stringIndex] != '/') {
		if (dateString[stringIndex] == '\0' || !isDigit(dateString[stringIndex])) {
			throw std::invalid_argument("Invalid date string");
		}
		day = day * 10 + dateString[stringIndex] - '0';
		stringIndex++;
	}

	stringIndex++;

	while (dateString[stringIndex] != '/') {
		if (dateString[stringIndex] == '\0' || !isDigit(dateString[stringIndex])) {
			throw std::invalid_argument("Invalid date string");
		}
		month = month * 10 + dateString[stringIndex] - '0';
		stringIndex++;
	}

	stringIndex++;

	while (dateString[stringIndex] != '\0') {
		if (!isDigit(dateString[stringIndex])) {
			throw std::invalid_argument("Invalid date string");
		}
		year = year * 10 + dateString[stringIndex] - '0';
		stringIndex++;
	}

	this->setDay(day);
	this->setMonth(month);
	this->setYear(year);
}

void Date::print(std::ostream& os) const
{
	const unsigned year = this->getYear();
	const unsigned month = this->getMonth();
	const unsigned day = this->getDay();

	if (day < 10) os << "0";
	os << day << '/';
	if (month < 10) os << '0';
	os << month << '/';
	os << year;
}

unsigned Date::getDay() const
{
	return this->day;
}

unsigned Date::getMonth() const
{
	return this->month;
}

unsigned Date::getYear() const
{
	return this->year + 1970;
}

void Date::setDay(unsigned day)
{
	if (day > 31) {
		throw std::invalid_argument("Day greater than 31");
	}
	if (this->getMonth() != 0 && day > MAX_DAYS_MONTH[this->getMonth() - 1]) {
		throw std::invalid_argument("Invalid day for given month");
	}
	if (this->getMonth() == 2 && !isLeapYear(this->getYear()) && day > 28) {
		throw std::invalid_argument("Invalid day for given month and year");
	}

	this->day = day;
}

void Date::setMonth(unsigned month)
{
	if (month < 1 || month > 12) {
		throw std::invalid_argument("Invalid month");
	}

	this->month = month;
}

void Date::setYear(unsigned year)
{
	if (year < 1970 || year > 2033) {
		throw std::invalid_argument("Invalid year");
	}
	year -= 1970;
	this->year = year;
}
