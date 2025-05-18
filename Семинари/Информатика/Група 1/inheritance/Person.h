#pragma once

#include <iostream>
#include <exception>

class Person
{
public:
    Person(const char* n, int age)
    {
        if (!n || age <= 0)
            throw std::invalid_argument("Bad name or age!");
        name = strcpy(new char[strlen(n) + 1], n);
        this->age = age;
    }

    Person(const Person& p)
        : name(nullptr), age(p.age)
    {
        name = strcpy(new char[strlen(p.name) + 1], p.name);
    }

    Person(Person&& p) noexcept
        : name(nullptr), age(p.age)
    {
        std::swap(name, p.name);
    }

    virtual ~Person() noexcept
    {
        delete[] name;
    }

    virtual Person* clone() const
    {
        return new Person(*this);
    }

    Person& operator=(const Person& p)
    {
        if (&p != this) {
            char* n = strcpy(new char[strlen(p.name) + 1], p.name);
            delete[] name;
            name = n;
            age = p.age;
        }
        return *this;
    }

    Person& operator=(Person&& p) noexcept
    {
        if (&p != this) {
            std::swap(name, p.name);
            age = p.age;
        }
        return *this;
    }

    virtual void print(std::ostream& out = std::cout) const
    {
        out << "Person\n\tName:\t" << name << "\n\tAge:\t" << age << "\n";
    }

    const char* getName() const noexcept
    {
        return name;
    }

    int getAge() const noexcept
    {
        return age;
    }

private:
    char* name;
    int age;
};

inline std::ostream& operator<<(std::ostream& os, const Person& p)
{
    p.print(os);
    return os;
}
