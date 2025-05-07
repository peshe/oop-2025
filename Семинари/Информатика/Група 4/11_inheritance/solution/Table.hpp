#ifndef TABLE_HPP
#define TABLE_HPP
#include "Furniture.hpp"

enum class TableType {
    LIVING_ROOM,
    KITCHEN
};

class Table : public Furniture {
    TableType type;

public:
    Table(const char *name, double h, double w, double l, TableType t);

    void displayCharacteristics() const override;

    [[nodiscard]] double calculatePrice() const override;

    [[nodiscard]] Furniture * clone() const override;
};


#endif //TABLE_HPP
