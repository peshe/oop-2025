#pragma once
#include <cstring>
#include <ostream>
#include <istream>


enum class Currency {
    UNKNOWN = -1,
    BGN,
    USD,
    EUR
};

inline std::ostream &operator<<(std::ostream &os, Currency currency) {
    switch (currency) {
        case Currency::BGN: {
            os << "BGN";
            break;
        }
        case Currency::USD: {
            os << "USD";
            break;
        }
        case Currency::EUR: {
            os << "EUR";
            break;
        }
        default: {
            os << "???";
        }
    }
    return os;
}

inline std::istream &operator>>(std::istream &is, Currency &currency) {
    char buffer[4];

    is >> buffer;
    if (std::strcmp(buffer, "BGN") == 0) {
        currency = Currency::BGN;
    } else if (std::strcmp(buffer, "USD") == 0) {
        currency = Currency::USD;
    } else if (std::strcmp(buffer, "EUR") == 0) {
        currency = Currency::EUR;
    } else {
        currency = Currency::UNKNOWN;
    }

    return is;
}
