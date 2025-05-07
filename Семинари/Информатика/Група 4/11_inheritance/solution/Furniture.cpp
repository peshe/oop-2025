#include "Furniture.hpp"
#include <iostream>


Furniture::Furniture(const Furniture &other) : Furniture(other.modelName, other.height, other.width, other.length) {
}

Furniture & Furniture::operator=(const Furniture &other) {
    if (this != &other) {
        delete this->modelName;
        this->modelName = StringHelpers::duplicateString(other.modelName);
        this->height = other.height;
        this->width = other.width;
        this->length = other.length;
    }
    return *this;
}

void Furniture::displayCharacteristics() const {
    std::cout << "Модел: " << modelName << std::endl;
    std::cout << "  Височина: " << height << " см" << std::endl;
    std::cout << "  Широчина: " << width << " см" << std::endl;
    std::cout << "  Дължина: " << length << " см" << std::endl;
}
