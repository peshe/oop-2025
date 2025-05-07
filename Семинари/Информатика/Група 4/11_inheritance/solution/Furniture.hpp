#ifndef FURNITURE_HPP
#define FURNITURE_HPP

#include "StringHelpers.hpp"

class Furniture {
protected:
    char *modelName;
    double height;
    double width;
    double length;

public:
    Furniture(const char *name, double h, double w, double l)
        : height(h), width(w), length(l) {
        modelName = StringHelpers::duplicateString(name);
    }

    Furniture(const Furniture & other);

    Furniture &operator=(const Furniture &other);

    virtual ~Furniture() {
        delete[] modelName;
    }

    [[nodiscard]] virtual Furniture* clone() const = 0;

    virtual void displayCharacteristics() const;

    [[nodiscard]] virtual double calculatePrice() const = 0;

    [[nodiscard]] const char *getModelName() const {
        return this->modelName;
    }
};


#endif //FURNITURE_HPP
