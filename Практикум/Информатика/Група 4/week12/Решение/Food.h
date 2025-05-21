#ifndef FOOD_H
#define FOOD_H

#include <ostream>

enum class DietType;

class Food {
protected:
    char* name;
    int healthBonus;
    constexpr static unsigned int MAX_NAME_LENGTH = 100;
public:
    Food(const char* name, int healthBonus);
    Food(const Food& other);
    Food(Food&& other) noexcept;
    virtual ~Food();

    Food& operator=(const Food& other);
    Food& operator=(Food&& other) noexcept;

    const char* getName() const { return name; }
    int getHealthBonus() const { return healthBonus; }
    
    virtual bool isCompatibleWith(DietType diet) const = 0;

    friend std::ostream& operator<<(std::ostream& os, const Food& food);

protected:
    void setName(const char* newName);
};

class MeatFood : public Food {
public:
    MeatFood(const char* name, int healthBonus);
    virtual bool isCompatibleWith(DietType diet) const override;
};

class FruitFood : public Food {
public:
    FruitFood(const char* name, int healthBonus);
    virtual bool isCompatibleWith(DietType diet) const override;
};

class MixedFood : public Food {
public:
    MixedFood(const char* name, int healthBonus);
    virtual bool isCompatibleWith(DietType diet) const override;
};

class Beef : public MeatFood {
public:
    Beef();
};

class Pork : public MeatFood {
public:
    Pork();
};

class Banana : public FruitFood {
public:
    Banana();
};

class Apple : public FruitFood {
public:
    Apple();
};

class Strawberry : public FruitFood {
public:
    Strawberry();
};

class FruitSalad : public FruitFood {
public:
    FruitSalad();
};

class MixedMeal : public MixedFood {
public:
    MixedMeal();
};

#endif