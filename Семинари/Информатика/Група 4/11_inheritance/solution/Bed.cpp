#include "Bed.hpp"
#include <iostream>

Bed::Bed(const char *name, double h, double w, double l) : Furniture(name, h, w, l) {
}

void Bed::displayCharacteristics() const {
    std::cout << "Легло:" << std::endl;
    Furniture::displayCharacteristics();
    std::cout << "  Цена:" << this->calculatePrice() << std::endl;
}

double Bed::calculatePrice() const {
    return this->length * this->height * 22.0;
}

Furniture * Bed::clone() const {
    return new Bed(*this);
}
