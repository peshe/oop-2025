#include <memory>
#include <fstream>

#include "World.hpp"

World* createWorld() {
    World* world = new(std::nothrow) World;
    if (world == nullptr) {
        return nullptr;
    }

    world->numPeople = 0;
    world->people = nullptr;

    return world;
}

void freeWorld(World*& world) {
    if (world == nullptr) {
        return;
    }

    for (size_t i = 0; i < world->numPeople; i++)
    {
        delete world->people;
    }

    delete world;
    world = nullptr;
    
}

void addCharacter(World* world, Character* charackter) {
    if (charackter == nullptr || world == nullptr){ 
        return;
    }

    Character** characters = new Character*[world->numPeople+1];
    for (size_t i = 0; i < world->numPeople; i++)
    {
        characters[i] = world->people[i];
    }

    // Може и на един ред std::memset(characters, sizeof(charackter), world->numPeople)
    characters[world->numPeople++] = charackter;
    delete world->people;
    world->people = characters;
}

// Да има повторение, но е нарочно защото ще видим как в бъдеще има добро решение
int getBonusSafe2(Weapon* weapon){
    return (weapon==nullptr)?0:weapon->power;
}

int getFullAttack(Character* character){
    return character->attackPower*getBonusSafe2(character->weapon);
}

Character* mostPowerfull(World* world) {
    if (world->numPeople == 0){
        return nullptr;
    }
    Character* mostPowerfullCharacter = world->people[0];
    for (size_t i = 1; i < world->numPeople; i++)
    {
        if ( getFullAttack(world->people[i]) >
             getFullAttack(mostPowerfullCharacter)) {
                mostPowerfullCharacter = world->people[i];
        }
    }
    return mostPowerfullCharacter;
}

size_t factoriel(int a){
    if (a == 1) {
        return 1;
    }
    return a*factoriel(a-1);
}

size_t cup(World* world) {
    if (world == nullptr) {
        return 0;
    }
    if (world->numPeople == 0) {
        return 0;
    }

    return world->numPeople*(world->numPeople-1)/2;
}

void saveWorld(World* world, const char* filename) {
    if (world == nullptr || filename == nullptr) {
        return;
    }

    std::ofstream file(filename, std::ios::out | std::ios::trunc);
    
    if (!file) {
        return;
    }

    file << world->numPeople << "\n";
    file.flush();
    for (size_t i = 0; i < world->numPeople; i++)
    {
        file << world->people[i]->attackPower << "\n"
             << world->people[i]->life << "\n"
             << world->people[i]->name << "\n"
             << world->people[i]->weapon->power << "\n";
    }
    file.flush();
    file.close();
}

World* loadWorld(const char* filename) {
    if (filename == nullptr) {
        return nullptr;
    }
    std::ifstream file = std::ifstream(filename, std::ios::in);
    if (!file) {
        return nullptr;
    }
    World* world = new (std::nothrow) World;
    if (world == nullptr) {
        return nullptr;
    }
    file >> world->numPeople;
    world->people = new Character*[world->numPeople];
    for (size_t i = 0; i < world->numPeople && file; i++)
    {
        int attackPower;
        int life;
        char name[SIZE_NAME];
        file >> attackPower
            >> life;
        file.ignore();
        file.getline(name, SIZE_NAME);
        int weaponPower;
        file >> weaponPower;
        world->people[i] = createCharacterWithParams(life,
                                attackPower,
                                name,
                                createWeaponWithParam(weaponPower));
    }
    return world;
}

