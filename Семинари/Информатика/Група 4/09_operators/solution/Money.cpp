#include "Money.hpp"

#include <cassert>


Money::Money(double startingMoney, Currency currency)
    : amount(startingMoney), currency(currency) {
}

double Money::getAmount() const {
    return this->amount;
}

Currency Money::getCurrency() const {
    return this->currency;
}

Money Money::softConvert(const ConversionRate &conversionRate) const {
    Money result = *this;
    result.hardConvert(conversionRate);
    return result;
}

void Money::hardConvert(const ConversionRate &conversionRate) {
    assert(this->currency == conversionRate.oldCurrency);

    this->amount *= conversionRate.conversionRate;
    this->currency = conversionRate.newCurrency;
}

Money Money::operator+(double amount) const {
    return Money(this->amount + amount, currency);
}

Money Money::operator+(const Money &money) const {
    assert(this->currency == money.currency);

    return Money(this->amount + money.amount, currency);
}

Money Money::operator-(double amount) const {
    return (*this) + (-amount);
}

Money Money::operator-(const Money &other) const {
    return (*this) + (-other);
}

Money &Money::operator+=(double amount) {
    this->amount += amount;

    return *this;
}

Money &Money::operator+=(const Money &other) {
    assert(this->currency == other.currency);

    this->amount += other.amount;

    return *this;
}

Money &Money::operator-=(double amount) {
    *this += -amount;

    return (*this);
}

Money &Money::operator-=(const Money &other) {
    *this += -other;

    return (*this);
}

Money Money::operator-() const {
    return Money(-this->amount, this->currency);
}

bool Money::operator==(const Money &other) const {
    assert(this->currency == other.currency);
    return this->amount == other.amount;
}

bool Money::operator!=(const Money &other) const {
    return !(*this == other);
}

bool Money::operator<(const Money &other) const {
    assert(this->currency == other.currency);
    return this->amount < other.amount;
}

bool Money::operator<=(const Money &other) const {
    return (*this < other) ||
           (*this == other);
}

bool Money::operator>(const Money &other) const {
    return other < *this;
}

bool Money::operator>=(const Money &other) const {
    return other <= *this;
}
