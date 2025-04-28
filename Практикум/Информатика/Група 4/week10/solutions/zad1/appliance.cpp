#include "appliance.hpp"
#include "socket.hpp"
#include <cstring>
#include <new>
#include <iostream>
#include <fstream>

unsigned Appliance::nextID = 0;

void Appliance::copy(const Appliance &other)
{
    unsigned brandLen = strlen(other.brand);
    unsigned descLen = strlen(other.description);
    this->brand = new (std::nothrow) char[brandLen + 1];
    if (this->brand == nullptr)
    {
        std::cerr << "Error allocating string" << std::endl;
    }
    strcpy(this->brand, other.brand);
    this->description = new (std::nothrow) char[descLen + 1];
    if (this->description == nullptr)
    {
        std::cerr << "Error allocating string" << std::endl;
    }
    strcpy(this->description, other.description);
    this->power = other.power;
    turnedOn = false;
    pluggedIn = false;
    sck = nullptr;
}

Appliance::Appliance(const char *brand, const char *description, unsigned power) : id(Appliance::nextID++)
{
    unsigned brandLen = strlen(brand);
    unsigned descLen = strlen(description);
    this->brand = new (std::nothrow) char[brandLen + 1];
    if (this->brand == nullptr)
    {
        std::cerr << "Error allocating string" << std::endl;
    }
    strcpy(this->brand, brand);
    this->description = new (std::nothrow) char[descLen + 1];
    if (this->description == nullptr)
    {
        std::cerr << "Error allocating string" << std::endl;
    }
    strcpy(this->description, description);
    this->power = power;
    this->turnedOn = false;
    this->pluggedIn = false;
    this->sck = nullptr;
}

Appliance::Appliance(std::istream &is) : id(nextID++)
{
    brand = nullptr;
    description = nullptr;
    is >> *this;
}

Appliance::~Appliance()
{
    delete[] brand;
    delete[] description;
}

Appliance::Appliance(const Appliance &other) : id(nextID++)
{
    copy(other);
}

Appliance &Appliance::operator=(const Appliance &other)
{
    if (this != &other)
    {
        delete[] brand;
        delete[] description;
        copy(other);
    }
    return *this;
}

bool Appliance::operator==(const Appliance &other) const
{
    if (!strcmp(brand, other.brand) && !strcmp(description, other.description) && power == other.power)
    {
        return true;
    }
    return false;
}

bool Appliance::operator!=(const Appliance &other) const
{
    return !(*this == other);
}

bool Appliance::operator>(const Appliance &other) const
{
    return power > other.power;
}

bool Appliance::operator<(const Appliance &other) const
{
    return power < other.power;
}

void Appliance::writeFile(char *filename) const
{
    std::ofstream of(filename, std::ios::app);
    if (!of.is_open())
    {
        throw std::runtime_error("Err opening file!");
    }
    of << *this;
    of.close();
}

void Appliance::readFile(char *filename)
{
    std::ifstream ifstr(filename);
    if (!ifstr.is_open())
    {
        throw std::runtime_error("Err opening file!");
    }
    ifstr >> *this;
    ifstr.close();
}

void Appliance::setTurnedOn(bool val)
{
    if (val == turnedOn)
    {
        return;
    }
    turnedOn = pluggedIn ? val : false;
    if (sck)
    {
        unsigned index = 0;
        for (size_t i = 0; i < sck->getSize(); i++)
        {
            if (sck->operator[](i) == this)
            {
                index = i;
                break;
            }
        }
        sck->turnOnOffDevice(index, val);
    }
}

std::ostream &operator<<(std::ostream &of, const Appliance &obj)
{
    of << obj.brand << "\n";
    of << obj.description << "\n";
    of << obj.power << "\n";
    return of;
}

std::istream &operator>>(std::istream &is, Appliance &source)
{
    char *buffer = nullptr;
    Appliance obj;
    try
    {
        buffer = new char[1001];
        is.getline(buffer, 1001);
        obj.brand = new char[strlen(buffer) + 1];
        strcpy(obj.brand, buffer);
        is.getline(buffer, 1001);
        obj.description = new char[strlen(buffer) + 1];
        strcpy(obj.description, buffer);
        is >> obj.power;
        is.ignore();
        delete[] source.brand;
        source.brand = obj.brand;
        obj.brand = nullptr;
        delete[] source.description;
        source.description = obj.description;
        obj.description = nullptr;
        source.power = obj.power;
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
        delete[] obj.brand;
        delete[] obj.description;
    }
    delete[] buffer;
    return is;
}
