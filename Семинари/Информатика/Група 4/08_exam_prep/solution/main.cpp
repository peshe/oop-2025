#include <iostream>
#include <fstream>
#include "car.hpp"
#include "dealership.hpp"
#include <cstring>

bool brandPredicate(const Car &car) {
    return std::strcmp(car.getBrand(), "Volkswagen") == 0;
}

int main() {
    std::ifstream ifs("objects.txt");
    if (!ifs.is_open()) return -1;

    try {
        Dealership ds(10);
        ds.add(Car(ifs), 1000.0);
        ds.add(Car(ifs), 2000.0);
        ds.add(Car(ifs), 3000.0);
        ds.print();
        std::cout << "------\n";
        ds.printCriteria(std::cout, &brandPredicate);
        std::cout << "------\n";
        ds.sell(1);
        ds.print();
        ds.printStats();
    } catch (const std::exception &ex) {
        std::cerr << ex.what() << '\n';
    }
    catch (...) {
        std::cerr << "Exception occurred\n";
    }

    ifs.close();

    return 0;
}
