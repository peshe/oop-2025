#include "car.hpp"
#include "person.hpp"

void Car::setOwner(Person* who)
{ 
    if (owner == who) return;

    if (owner) owner->addNewCar(nullptr);
    owner = who;
    if (owner) owner->addNewCar(this);
}

void Car::print() const
{
    std::cout << "A car " << model;
    if (owner) {
        std::cout << " and I have an owner.";
    }
    else {
        std::cout << " and I am all alone.";
    }
    std::cout << std::endl;
}

Car::~Car()
{
    std::cout << "~Car()\n";
    if (owner) owner->addNewCar(nullptr);
}


Car& Car::operator=(Car&& other) noexcept
{
    std::cout << "Car& operator=(Car&&)\n";
    strcpy(model, other.model);
    if (owner) owner->addNewCar(nullptr);
    owner = other.owner;
    if (owner) owner->addNewCar(this);
    other.owner = nullptr;
    return *this;
}
