#pragma once
#include "Person.h"
class Student : public Person
{
public:
    Student(const char* uni) :
        Person("Gosho", 22)
    {
        uni_name = new char[strlen(uni) + 1];
        strcpy(uni_name, uni);
    }

    Student(const Student& s) :
        Person(s)
    {
        uni_name = new char[strlen(s.uni_name) + 1];
        strcpy(uni_name, s.uni_name);
    }

    virtual ~Student() noexcept override
    {
        delete[] uni_name;
    }

    Student& operator=(const Student& s)
    {
        if (&s != this) {
            char* n = strcpy(new char[strlen(s.uni_name) + 1], s.uni_name);
            try {
                Person::operator=(s);
            }
            catch (...) {
                delete[] n;
                throw;
            }
            delete[] uni_name;
            uni_name = n;
        }
        return *this;
    }

    virtual Student* clone() const override
    {
        return new Student(*this);
    }

private:
    char* uni_name;
};

