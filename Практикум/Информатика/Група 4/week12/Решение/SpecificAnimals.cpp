#include "SpecificAnimals.h"

Lion::Lion(const char* name) 
    : Animal(name, 200, DietType::MEAT) {}

void Lion::roar() {
}

void Lion::attack(Animal& target) {
    target.takeDamage(30);
}

bool Lion::feed(const Food& food) {
    bool success = Animal::feed(food);
    if (success) {
        increaseBloodCells(food.getHealthBonus());
    }
    return success;
}

Dragon::Dragon(const char* name) 
    : Animal(name, 150, DietType::MIXED) {}

void Dragon::fire(Animal& target) {
    target.takeDamage(target.getBloodCells() / 2);
}

void Dragon::attack(Animal& target) {
    fire(target);
}

Eagle::Eagle(const char* name) 
    : Animal(name, 100, DietType::FRUIT) {}

void Eagle::fly(Animal& target) {
    target.takeDamage(20);
}

void Eagle::attack(Animal& target) {
    fly(target);
}

Scorpion::Scorpion(const char* name) 
    : Animal(name, 50, DietType::FRUIT) {}

void Scorpion::poison(Animal& target) {
    target.takeDamage(50);
}

void Scorpion::attack(Animal& target) {
    poison(target);
}

Chimera::Chimera(const char* name) 
    : Animal(name, 200, DietType::MIXED), Dragon(name), Lion(name) {}

void Chimera::attack(Animal& target) {
    Dragon::fire(target);
    Lion::attack(target);
}

bool Chimera::feed(const Food& food) {
    return Lion::feed(food);
}

Griffin::Griffin(const char* name) 
    : Animal(name, 200, DietType::FRUIT), Lion(name), Eagle(name) {}

void Griffin::attack(Animal& target) {
    Eagle::fly(target);
    Lion::attack(target);
}

bool Griffin::feed(const Food& food) {
    return Lion::feed(food);
}

Manticore::Manticore(const char* name) 
    : Animal(name, 100, DietType::MIXED), Eagle(name), Lion(name), Scorpion(name) {}

void Manticore::attack(Animal& target) {
    Eagle::fly(target);
    Lion::attack(target);
    Scorpion::poison(target);
}

bool Manticore::feed(const Food& food) {
    return Lion::feed(food);
}