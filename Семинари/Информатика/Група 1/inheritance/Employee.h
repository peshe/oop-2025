#pragma once
#include "Person.h"

class Employee : public Person
{
public:
    Employee(const char* name, int age, float sal)
        : Person(name, age), salary(sal)
    {
        if (sal < 0)
            throw std::invalid_argument("Bad salary value");
    }

    virtual double getSalary() const
    {
        return salary;
    }

    virtual void print(std::ostream& out = std::cout) const override
    {
        Person::print(out);
        out << "\tSalary: " << salary << "\n";
    }

    virtual Employee* clone() const override
    {
        return new Employee(*this);
    }

private:
    float salary;
};

class Secretary : public Employee
{
public:
    Secretary(float salary) : Employee("Maria", 67, salary) {}
    virtual void print(std::ostream& out = std::cout) const override
    {
        Employee::print();
        out << "I am a secretary!\n";
    }
    virtual Secretary* clone() const override
    {
        return new Secretary(*this);
    }
};

class Manager : public Employee
{
public:
    Manager(const char* name, int age, float sal)
        : Employee(name, age, sal)
        , team(nullptr), size(0){
    }

    Manager(const Manager& m)
        : Employee(m)
    { 
        copy(m.team, m.size);
    }

    ~Manager() noexcept override
    {
        clear(team, size);
    }

    Manager& operator=(const Manager& m)
    {
        if (&m != this) {
            Manager copy(m);
            Employee::operator=(std::move(copy));
            std::swap(copy.team, team);
            std::swap(copy.size, size);
        }
        return *this;
    }

    bool hire(const Employee& e)
    {
        Employee** newTeam = nullptr;
        try {
            newTeam = new Employee * [size + 1];
            newTeam[size] = e.clone();
        }
        catch (...) {
            delete[] newTeam;
            return false;
        }

        for (int i = 0; i < size; ++i) {
            newTeam[i] = team[i];
        }
        ++size;
        delete[] team;
        team = newTeam;
        return true;
    }

    virtual void print(std::ostream& out = std::cout) const override
    {
        Person::print(out);
        out << "------------Team--------------\n";
        for (int i = 0; i < size; ++i) {
            team[i]->print(out);
        }
        out << "\tSalary: " << getSalary();
    }

    virtual double getSalary() const
    {
        double s = 0;
        for (int i = 0; i < size; ++i) {
            s += team[i]->getSalary();
        }
        return Employee::getSalary() + 0.1 * s;
    }

    virtual Manager* clone() const override
    {
        return new Manager(*this);
    }

private:
    void clear(Employee** team, int size) noexcept
    {
        for (int i = size - 1; i >= 0; --i) {
            delete team[i];
        }
        delete[] team;
    }

    void copy(Employee** newTeam, int newSize)
    {
        size = newSize;
        team = new Employee * [newSize];
        for (int i = 0; i < size; ++i) {
            team[i] = nullptr;
        }

        try {
            for (int i = 0; i < size; ++i) {
                team[i] = newTeam[i]->clone();
            }
        }
        catch (...) {
            clear(team, size);
            throw;
        }
    }

private:
    Employee** team;
    int size;
};
