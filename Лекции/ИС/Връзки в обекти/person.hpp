#pragma once
#include <new>
#include <cstring>

class Car;

class Person
{
public:
    //Person() = delete;
    Person(const Person&);
    Person(Person&&) noexcept;

    explicit Person(bool male);
    Person(bool male, const char* f, const char* m, const char* l);
    ~Person() noexcept;

    bool setFirstName(const char* name)
    {
        return setName(name, this->firstName);
    }
    bool setMiddleName(const char* name)
    {
        return setName(name, this->midName);
    }
    bool setLastName(const char* name)
    {
        return setName(name, this->lastName);
    }
    const char* getFirstName() const
    {
        return firstName;
    }

    Person& operator=(const Person& p);
    Person& operator=(Person&& p) noexcept;

    void addNewCar(Car* c);
    const Car* getMyCar() const { return vehicle; }

    void print() const;

private:
    bool setName(const char* name, char*& oldName)
    {
        if (!name || name == oldName) return false;

        char* newName = new(std::nothrow) char[strlen(name) + 1];
        if (!newName) return false;

        delete[] oldName;
        oldName = newName;
        strcpy_s(oldName, strlen(name) + 1, name);
        return true;
    }

    void clearData();

private:
    char* firstName;
    char* midName;
    char* lastName;

    const bool isMale;

    Car* vehicle = nullptr;
};
