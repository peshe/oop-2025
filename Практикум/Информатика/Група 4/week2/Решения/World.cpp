#include <memory>

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
