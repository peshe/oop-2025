#pragma once

struct Date {
    unsigned day{};
    unsigned month{};
    unsigned year{};
};

void printDate(const Date& date);
