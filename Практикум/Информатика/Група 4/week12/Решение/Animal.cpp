#include "Animal.h"
#include <iostream>
#include <cstring>

int Animal::nextId = 1;

void Animal::setName(const char* newName) {
    if (name) {
        delete[] name;
        name = nullptr;
    }
    if (newName) {
        size_t len = strlen(newName);
        if (len > MAX_NAME_LENGTH) {
            len = MAX_NAME_LENGTH;
        }
        name = new char[len + 1];
        strncpy(name, newName, len);
        name[len] = '\0';
    } else {
        name = nullptr;
    }
}

Animal::Animal(const char* name, int bloodCells, DietType diet)
    : name(nullptr), id(nextId++), bloodCells(bloodCells), diet(diet) {
    setName(name);
}

Animal::Animal(const Animal& other)
    : name(nullptr), id(nextId++), bloodCells(other.bloodCells), diet(other.diet) {
    setName(other.name);
}

Animal::Animal(Animal&& other) noexcept
    : name(other.name), id(nextId++), bloodCells(other.bloodCells), diet(other.diet) {
    other.name = nullptr;
}

Animal& Animal::operator=(const Animal& other) {
    if (this != &other) {
        setName(other.name);
        bloodCells = other.bloodCells;
        diet = other.diet;
    }
    return *this;
}

Animal& Animal::operator=(Animal&& other) noexcept {
    if (this != &other) {
        delete[] name;
        name = other.name;
        bloodCells = other.bloodCells;
        diet = other.diet;
        id = other.id;
        other.name = nullptr;
    }
    return *this;
}

Animal::~Animal() {
    delete[] name;
}

bool Animal::feed(const Food& food) {
    bool canEat = food.isCompatibleWith(diet);

    if (canEat) {
        increaseBloodCells(food.getHealthBonus());
        return true;
    }
    return false;
}

void Animal::increaseBloodCells(int amount) {
    bloodCells += amount;
}

void Animal::decreaseBloodCells(int amount) {
    bloodCells = std::max(0, bloodCells - amount);
}

std::ostream& operator<<(std::ostream& os, const Animal& animal) {
    os << "Name: " << animal.name << "\n";
    os << "ID: " << animal.id << "\n";
    os << "Blood cells: " << animal.bloodCells << "\n";
    os << "Diet type: ";
    switch (animal.diet) {
        case DietType::MEAT: os << "Carnivore"; break;
        case DietType::FRUIT: os << "Herbivore"; break;
        case DietType::MIXED: os << "Omnivore"; break;
    }
    os << "\n";
    return os;
}