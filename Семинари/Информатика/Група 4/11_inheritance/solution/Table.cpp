#include "Table.hpp"
#include <iostream>

const char *tableTypeToString(TableType type) {
    switch (type) {
        case TableType::LIVING_ROOM: return "Холова";
        case TableType::KITCHEN: return "Кухненска";
        default: return "Неизвестен тип";
    }
}

Table::Table(const char *name, double h, double w, double l, TableType t)
    : Furniture(name, h, w, l), type(t) {
}

void Table::displayCharacteristics() const {
    std::cout << "Маса: " << std::endl;
    Furniture::displayCharacteristics();
    std::cout << "  Тип: " << tableTypeToString(type) << std::endl;
    std::cout << "  Цена: " << calculatePrice() << " лв." << std::endl;
}

double Table::calculatePrice() const {
    return width * length * 15.0;
}

Furniture * Table::clone() const {
    return new Table(*this);
}
