#include "Date.h"

#include <iostream>
#include <iomanip>

void printDate(const Date& date) {
    std::cout << std::setw(2) << std::setfill('0') << date.day;
    std::cout << std::setw(0) << std::setfill(' ') << '/';

    std::cout << std::setw(2) << std::setfill('0') << date.month;
    std::cout << std::setw(0) << std::setfill(' ') << '/' ;
    
    std::cout << std::setw(4) << std::setfill('0') << date.year;
    std::cout << std::setw(0) << std::setfill(' ');
}
