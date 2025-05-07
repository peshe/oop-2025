#ifndef CHAIR_HPP
#define CHAIR_HPP
#include "Furniture.hpp"

enum class ChairType {
    WOODEN,
    METAL,
    PLASTIC
};

class Chair : public Furniture {
    ChairType type;

public:
    Chair(const char *name, double h, double w, double l, ChairType type);

    void displayCharacteristics() const override;

    [[nodiscard]] double calculatePrice() const override;

    [[nodiscard]] Furniture * clone() const override;
};


#endif //CHAIR_HPP
