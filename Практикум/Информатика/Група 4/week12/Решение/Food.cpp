#include "Food.h"
#include "Animal.h"
#include <cstring>
#include <ostream>

void Food::setName(const char* newName) {
    if (name) {
        delete[] name;
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

Food::Food(const char* name, int healthBonus) 
    : name(nullptr), healthBonus(healthBonus) {
    setName(name);
}

Food::~Food() {
    delete[] name;
}

Food::Food(const Food& other) : name(nullptr), healthBonus(other.healthBonus) {
    setName(other.name);
}

Food::Food(Food&& other) noexcept : name(other.name), healthBonus(other.healthBonus) {
    other.name = nullptr;
}

Food& Food::operator=(const Food& other) {
    if (this != &other) {
        setName(other.name);
        healthBonus = other.healthBonus;
    }
    return *this;
}

Food& Food::operator=(Food&& other) noexcept {
    if (this != &other) {
        delete[] name;
        name = other.name;
        healthBonus = other.healthBonus;
        other.name = nullptr;
    }
    return *this;
}

std::ostream& operator<<(std::ostream& os, const Food& food) {
    os << "Food name: " << (food.name ? food.name : "none") << ", bonus: " << food.healthBonus;
    return os;
}

MeatFood::MeatFood(const char* name, int healthBonus)
    : Food(name, healthBonus) {}

bool MeatFood::isCompatibleWith(DietType diet) const {
    return diet == DietType::MEAT || diet == DietType::MIXED;
}

FruitFood::FruitFood(const char* name, int healthBonus)
    : Food(name, healthBonus) {}

bool FruitFood::isCompatibleWith(DietType diet) const {
    return diet == DietType::FRUIT || diet == DietType::MIXED;
}

MixedFood::MixedFood(const char* name, int healthBonus)
    : Food(name, healthBonus) {}

bool MixedFood::isCompatibleWith(DietType diet) const {
    return diet == DietType::MIXED;
}

Beef::Beef() : MeatFood("Beef", 20) {}
Pork::Pork() : MeatFood("Pork", 10) {}
Banana::Banana() : FruitFood("Banana", 10) {}
Apple::Apple() : FruitFood("Apple", 20) {}
Strawberry::Strawberry() : FruitFood("Strawberry", 10) {}
FruitSalad::FruitSalad() : FruitFood("Fruit Salad", 40) {}
MixedMeal::MixedMeal() : MixedFood("Stew", 70) {}