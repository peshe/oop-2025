#include <iostream>
#include "Weapon.hpp"

#include "Weapon.hpp"
#include "Character.hpp"
#include "World.hpp"

int main(int argc, char const *argv[])
{
    Weapon* chare = createWeaponWithParam(1);
    saveWeapon(chare, "baz.txt");
    Weapon* weapon = loadWeapon("baz.txt");
    std::cout << weapon->power << std::endl;
    saveWeapon(weapon, "baz2.txt");
    return 0;
}
