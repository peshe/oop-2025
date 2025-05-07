#include "Chair.hpp"
#include <iostream>

const char *chairTypeToString(ChairType type) {
    switch (type) {
        case ChairType::WOODEN: return "Дървен";
        case ChairType::METAL: return "Метален";
        case ChairType::PLASTIC: return "Пластмасов";
        default: return "Неизвестен тип";
    }
}

Chair::Chair(const char *name, double h, double w, double l, ChairType type)
    : Furniture(name, h, w, l), type(type) {
}

void Chair::displayCharacteristics() const {
    std::cout << "Стол: " << std::endl;
    Furniture::displayCharacteristics();
    std::cout << "  Тип: " << chairTypeToString(type) << std::endl;
    std::cout << "  Цена: " << calculatePrice() << " лв." << std::endl;
}

double Chair::calculatePrice() const {
    return height * width * 9.0;
}

Furniture * Chair::clone() const {
    return new Chair(*this);
}
