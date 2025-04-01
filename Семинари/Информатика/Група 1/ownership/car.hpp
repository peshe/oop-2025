#pragma once
#include <iostream>

class Person;

class Car
{
public:
    Car()
    {
        model[0] = 0;
        std::cout << "Car()\n";
    }
    Car(const char* model)
    {
        std::cout << "Car(const char* model)\n";
        if (!model) model = "";
        strcpy(this->model, model);
    }

    Car(const Car& other) = delete;
    void operator=(const Car& other) = delete;

    Car(Car&& other) noexcept
    {
        std::cout << "Car(Car&&)\n";
        strcpy(model, other.model);
    }

    Car& operator=(Car&& other) noexcept;
    ~Car();

    void setOwner(Person* who);
    void print() const;

private:
    char model[256];

    Person* owner = nullptr;
};

