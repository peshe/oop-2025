#ifndef BED_HPP
#define BED_HPP
#include "Furniture.hpp"


class Bed : public Furniture {
public:
    Bed(const char *name, double h, double w, double l);

    void displayCharacteristics() const override;

    [[nodiscard]] double calculatePrice() const override;

    [[nodiscard]] Furniture * clone() const override;
};


#endif //BED_HPP
