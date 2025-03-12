#include <iostream>
#include <new>
#include <fstream>

#include "Weapon.hpp"

Weapon* createWeaponWithParam(int param) {
    Weapon* weapon = new (std::nothrow)Weapon;
    if (weapon == nullptr) {
        std::cout << "ERROR: allocating resources" << std::endl;
        return nullptr;
    }
    weapon->power = param;
    return weapon;
}


// Едно решение на бонус задачата е с индекс на оръжията
Weapon indexWeapon[] = {
    {1},
    {2},
    {4},
    {8},
    {-1}
};

Weapon* getWeapon(int index) {
    if (sizeof(indexWeapon) <= index) {
        std::cout << "Indexing array out of bounds" << std::endl;
        return nullptr;
    }
    return createWeaponWithParam(indexWeapon[index].power);
}

Weapon* createWeapon() {
    int param;
    std::cout << "Enter weapon power:" << std::endl;
    std::cin >> param;
    return createWeaponWithParam(param);
}

void freeWeapon(Weapon*& weapon){
    if (weapon == nullptr) {
        std::cout << "Error: can not free empty weapon";
    }
    delete weapon;
    weapon = nullptr;
}

void saveWeapon(Weapon* weapon, const char* filename) {
    if (weapon == nullptr || filename == nullptr) {
        return;
    }
    std::ofstream file(filename, std::ios::out | std::ios::trunc);
    
    if (!file) {
        return;
    }

    file << weapon->power;
    
    file.flush();

    file.close();
}

Weapon* loadWeapon(const char* filename) {
    if (filename == nullptr) {
        return nullptr;
    }
    std::ifstream file(filename, std::ios::in);
    if (!file) {
        return nullptr;
    }
    
    Weapon* wep = new(std::nothrow) Weapon;
    if (wep == nullptr) {
        return nullptr;
    }
    file >> wep->power;

    file.close();
    return wep;
}