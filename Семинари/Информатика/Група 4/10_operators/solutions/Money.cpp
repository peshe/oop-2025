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

Money::operator int() const {
    return static_cast<int>(this->amount);
    // or C-style cast
    // return (int)this->amount;
}

Money::operator double() const {
    return this->getAmount();
}

Money operator+(double lhs, const Money &rhs) {
    // Reuse the member operator+: Money + double
    return rhs + lhs;
}

Money operator+(int lhs, const Money &rhs) {
    // Reuse the double operator
    return static_cast<double>(lhs) + rhs;
}

std::ostream &operator<<(std::ostream &os, const Money &money) {
    // TODO: Maybe add precision
    os << money.getAmount() << '\t' << money.getCurrency();
    return os;
}

std::istream &operator>>(std::istream &is, Money &money) {
    double amount;
    Currency currency;
    if (!is) {
        throw std::invalid_argument("Invalid input stream");
    }

    if (is >> amount >> currency) {
        money.amount = amount;
        money.currency = currency;
    } else {
        is.setstate(std::ios_base::failbit);
    }
    return is;
}
