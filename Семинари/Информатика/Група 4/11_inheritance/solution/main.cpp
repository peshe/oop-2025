#include <iostream>

#include "Chair.hpp"
#include "Bed.hpp"
#include "InMemoryFurnitureCatalog.hpp"
#include "Table.hpp"

int main() {
    Chair c1("Chair1", 10, 20, 30, ChairType::METAL);
    Table t1("Table1", 10, 20, 30, TableType::KITCHEN);
    Bed b1("Bed1", 10, 20, 30);

    InMemoryFurnitureCatalog catalog(3);
    catalog.create(c1);
    catalog.create(t1);
    catalog.create(b1);
    catalog.read("Table1").displayCharacteristics();
    catalog.read("Bed1").displayCharacteristics();

    Chair c2("Chair2", 10, 20, 30, ChairType::METAL);
    catalog.create(c2);
    catalog.read("Chair2").displayCharacteristics();

    try {
        catalog.remove("Chair3");
    } catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
    }

    catalog.remove("Chair2");
    try {
        catalog.read("Chair2");
    } catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
    }

    Bed b2("Bed2", 10, 20, 303);
    catalog.update("Bed1", b2);
    catalog.read("Bed2").displayCharacteristics();

    try {
        catalog.read("Bed1");
    } catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}
