#ifndef ANIMAL_H
#define ANIMAL_H

#include <iostream>
#include <cstring>
#include "Food.h"

enum class DietType {
    MEAT,
    FRUIT,
    MIXED
};

class Animal {
protected:
    char* name;
    int id;
    int bloodCells;
    DietType diet;

    static int nextId;

    constexpr static unsigned int MAX_NAME_LENGTH = 100;

public:
    Animal(const char* name, int bloodCells, DietType diet);
    Animal(const Animal& other);
    Animal(Animal&& other) noexcept;
    Animal& operator=(const Animal& other);
    Animal& operator=(Animal&& other) noexcept;
    virtual ~Animal();

    const char* getName() const { return name; }
    int getId() const { return id; }
    int getBloodCells() const { return bloodCells; }
    DietType getDiet() const { return diet; }

    virtual bool feed(const Food& food);
    virtual void attack(Animal& target) = 0;
    
    virtual void takeDamage(int amount) { decreaseBloodCells(amount); }

    friend std::ostream& operator<<(std::ostream& os, const Animal& animal);

protected:
    void setName(const char* newName);
    void increaseBloodCells(int amount);
    virtual void decreaseBloodCells(int amount);
};

#endif