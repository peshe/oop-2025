#include "Person.hpp"

#include <new>
#include <cassert>
#include <cstring>
#include <iostream>
#include "car.hpp"

Person::Person(const Person& p) : 
    firstName(nullptr), 
    midName(nullptr), 
    lastName(nullptr),
    isMale(p.isMale)
{
    std::cout << "Person::Person(const Person & p)\n";

    if (!setFirstName(p.firstName) ||
        !setMiddleName(p.midName) ||
        !setLastName(p.lastName)) {
        clearData();
        throw "Bad name";
    }
}

Person::Person(bool male)
    : Person(male, "", "", "")
{
    std::cout << "Person::Person(bool male)\n";
}

Person::Person(bool male, const char* f, const char* m, const char* l) : 
    firstName(nullptr), 
    midName(nullptr), 
    lastName(nullptr), 
    isMale(male)
{
    std::cout << "Person::Person(bool male, const char* f, "
                 "const char* m, const char* l)\n";
    if (!setFirstName(f) || 
        !setMiddleName(m) ||
        !setLastName(l)) {
        clearData();
        throw "Bad name";
    }
}

Person::~Person()
{
    std::cout << "Person::~Person()\n";
    clearData();

    if (vehicle) 
        vehicle->setOwner(nullptr);
}

void Person::clearData()
{
    delete[] firstName;
    delete[] midName;
    delete[] lastName;
}

Person::Person(Person&& other) noexcept : 
    isMale(other.isMale), 
    vehicle(other.vehicle)
{
    std::cout << "Person::Person(Person&& other)\n";

    firstName = other.firstName;
    midName = other.midName;
    lastName = other.lastName;

    other.firstName = other.midName = other.lastName = nullptr;
    other.vehicle = nullptr;

    if (vehicle) vehicle->setOwner(this);
}

Person& Person::operator=(Person&& p) noexcept
{
    std::cout << "Person::operator=(Person&& p)\n";
    std::swap(firstName, p.firstName);
    std::swap(midName, p.midName);
    std::swap(lastName, p.lastName);

    if (vehicle) vehicle->setOwner(nullptr);
    if (p.vehicle) {
        vehicle = p.vehicle;
        vehicle->setOwner(this);
        p.vehicle = nullptr;
    }
    else {
        vehicle = nullptr;
    }

    return *this;
}

Person& Person::operator=(const Person& p)
{
    if (this == &p) {
        return *this;
    }

    Person copy(p);
    *this = std::move(copy);
    // *this = Person(p);
    return *this;
}

void Person::addNewCar(Car* c)
{
    if (vehicle == c) return;

    if (c) {
        if (vehicle)
            vehicle->setOwner(nullptr);
        c->setOwner(this);
    }
    vehicle = c;
}

void Person::print() const
{
    std::cout << "I am " << firstName << ' '
        << midName[0] << ". " << lastName
        << " and ";
    if (vehicle) {
        std::cout << "have a car: ";
        vehicle->print();
        std::cout << std::endl;
    }
    else {
        std::cout << " I walk all the day and night." << std::endl;
    }
}
