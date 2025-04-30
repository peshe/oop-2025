#pragma once

#include <iosfwd>

#include "Currency.hpp"
#include "ConversionRate.hpp"


class Money {
public:
    Money(double startingMoney, Currency currency);

    double getAmount() const;

    Currency getCurrency() const;

    Money softConvert(const ConversionRate &conversionRate) const;

    void hardConvert(const ConversionRate &conversionRate);

    Money operator+(double amount) const;

    Money operator+(const Money &other) const;

    Money operator-(double amount) const;

    Money operator-(const Money &other) const;

    Money &operator+=(double amount);

    Money &operator+=(const Money &other);

    Money &operator-=(double amount);

    Money &operator-=(const Money &other);

    Money operator-() const;

    bool operator==(const Money &other) const;

    bool operator!=(const Money &other) const;

    bool operator<(const Money &other) const;

    bool operator<=(const Money &other) const;

    bool operator>(const Money &other) const;

    bool operator>=(const Money &other) const;

    // ============== New stuff:

    friend std::ostream &operator<<(std::ostream &os, const Money &money);

    friend std::istream &operator>>(std::istream &is, Money &money);

    operator int() const;

    explicit operator double() const;

private:
    double amount;
    Currency currency{Currency::UNKNOWN};
};

// Non-member operator overloads

Money operator+(double lhs, const Money &rhs);

Money operator+(int lhs, const Money &rhs);
