#pragma once

#include <cstdint>


class Date {
public:
    Date(std::uint8_t day, std::uint8_t month, std::uint16_t year);

    std::uint8_t getDay() const;

    std::uint8_t getMonth() const;

    std::uint16_t getYear() const;

    bool operator==(const Date &rhs) const;

    bool operator<(const Date &rhs) const;

private:
    std::uint8_t day;
    std::uint8_t month;
    std::uint16_t year;
};
