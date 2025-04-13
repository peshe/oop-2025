#include <stdexcept>
#include "StaticData.h"

StaticData::StaticData(int val) 
    : StaticData(val, "N/A")
{ }

StaticData::StaticData(int val, const char* name)
    : ID(StaticData::getNextId())
    , value(val)
    , name(nullptr)
{
    if (name == nullptr || name[0] == '\0')
        throw std::invalid_argument("Bad name!");
    this->name = strcpy(new char[strlen(name) + 1], name);
    ++instances;
}

StaticData::StaticData(const StaticData& other)
    : value(other.value), ID(StaticData::getNextId())
    , name(nullptr)
{
    char* text = new char[strlen(other.name) + 1];
    this->name = text;
    strcpy(this->name, other.name);
    ++instances;
}

StaticData::StaticData(StaticData&& other) noexcept
    : value(other.value), ID(StaticData::getNextId())
{
    ++instances;
    name = other.name;
    other.name = nullptr;
}

StaticData::~StaticData() noexcept
{
    --instances;
    delete[] name;
}

StaticData& StaticData::operator=(const StaticData& other)
{
    if (this == &other) return *this;

    if (!setName(other.name)) {
        throw std::bad_alloc();
    }
    value = other.value;
    return *this;
}

StaticData& StaticData::operator=(StaticData&& other) noexcept
{
    if (this != &other) {
        std::swap(name, other.name);
        value = other.value;
    }
    return *this;
}

int StaticData::getID() const noexcept
{
    return ID;
}

int StaticData::getNextId()
{
    return nextId++;
}

bool StaticData::setName(const char* name)
{
    if (!name || !name[0]) return false;

    char* copy = new(std::nothrow) char[strlen(name) + 1];
    if (!copy) return false;

    delete[] this->name;
    strcpy(copy, name);
    this->name = copy;
    return true;
}


int someFunction() { return 0; }

int StaticData::nextId = 0;
int StaticData::instances = someFunction();

StaticData StaticData::obj(17);
