#include <iostream>
#include "Weapon.hpp"

#include "Weapon.hpp"
#include "Character.hpp"
#include "World.hpp"

int main(int argc, char const *argv[])
{
    World* world = createWorld();
    addCharacter(world, createCharacter(createWeapon()));
    std::cout << mostPowerfull(world)->name;
    return 0;
}
