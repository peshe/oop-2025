#include "Client.hpp"

#include <cstring>
#include <cassert>
#include <new>
#include <stdexcept>


Client::Client(const char *name, const char *identificationNumber, const Date &birthday, const Money &money)
    : birthDay(birthday), money(money) {
    setIdentificationNumber(identificationNumber);
    setName(name);
}

Client::Client(const Client &other) : Client(other.name, other.identificationNumber, other.birthDay, other.money) {
}

Client &Client::operator=(const Client &other) {
    if (this != &other) {
        this->deleteData();
        this->copyDataFrom(other);
    }

    return *this;
}

Client::~Client() {
    this->deleteData();
}

const char *Client::getName() const {
    return this->name;
}

const char *Client::getIdentificationNumber() const {
    return this->identificationNumber;
}

const Date &Client::getBirthDay() const {
    return this->birthDay;
}

const Money &Client::getMoney() const {
    return this->money;
}

bool Client::deposit(const Money &toDeposit) {
    this->money += toDeposit;

    return true;
}

bool Client::withdraw(const Money &toWithdraw) {
    if (this->money < toWithdraw) {
        return false;
    }

    this->money -= toWithdraw;

    return true;
}

void Client::convert(const ConversionRate &conversionRate) {
    this->money.hardConvert(conversionRate);
}

void Client::copyDataFrom(const Client &other) {
    this->setName(other.name);
    this->setIdentificationNumber(other.identificationNumber);
    this->birthDay = other.birthDay;
    this->money = other.money;
}

void Client::deleteData() {
    delete[] this->name;
    this->name = nullptr;
}

void Client::setName(const char *name) {
    if (!name) {
        throw std::invalid_argument("Invalid name");
    }
    delete[] this->name;
    char *newName = new(std::nothrow) char[strlen(name) + 1];

    if (!newName) {
        throw std::bad_alloc();
    }

    strcpy(newName, name);
    this->name = newName;
}

void Client::setIdentificationNumber(const char *identificationNumber) {
    strcpy(this->identificationNumber, identificationNumber);
}
