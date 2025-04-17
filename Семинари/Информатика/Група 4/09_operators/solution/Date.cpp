#include "Date.hpp"

#include <cassert>


Date::Date(std::uint8_t day, std::uint8_t month, std::uint16_t year) {
    assert(day <= 31);
    assert(month <= 12);

    this->day = day;
    this->month = month;
    this->year = year;
}

std::uint8_t Date::getDay() const {
    return this->day;
}

std::uint8_t Date::getMonth() const {
    return this->month;
}

std::uint16_t Date::getYear() const {
    return this->year;
}

bool Date::operator==(const Date &rhs) const {
    return this->year == rhs.year &&
           this->month == rhs.month &&
           this->day == rhs.day;
}

bool Date::operator<(const Date &rhs) const {
    return this->year < rhs.year ||
           this->year == rhs.year && this->month < rhs.month ||
           this->year == rhs.year && this->month == rhs.month && this->day < rhs.day;
}
