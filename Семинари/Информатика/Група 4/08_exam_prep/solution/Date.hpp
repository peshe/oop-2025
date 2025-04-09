#pragma once

#include <cstdint>
#include <ostream>
#include <iostream>

class Date
{
public:
	Date() = default;

	Date(unsigned day, unsigned month, unsigned year);

	Date(const char* dateString);

	void print(std::ostream& os = std::cout) const;

	unsigned getDay() const;
	unsigned getMonth() const;
	unsigned getYear() const;

	void setDay(unsigned day);
	void setMonth(unsigned month);
	void setYear(unsigned year);

private:
	std::uint16_t day : 5;
	std::uint16_t month : 4;
	std::uint16_t year : 6;
};

