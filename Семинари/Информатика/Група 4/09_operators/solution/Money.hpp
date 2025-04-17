#pragma once

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

private:
    double amount;
    Currency currency{Currency::UNKNOWN};
};
