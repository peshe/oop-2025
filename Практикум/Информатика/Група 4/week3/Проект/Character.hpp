#pragma once
#ifndef CHARACTER_HPP
#define CHARACTER_HPP

#include "Weapon.hpp"

const size_t SIZE_NAME = 50;

struct Character
{
    int life;
    int attackPower;
    char name[SIZE_NAME];
    Weapon* weapon;
};

Character* createCharacterWithParams(
    int life,
    int attack,
    const char name[SIZE_NAME],
    Weapon* weapon);
Character* createCharacter(Weapon* weapon);
void freeCharacter(Character*& character);
bool isDead(Character* character);
void attack(Character* left, Character* right);

void saveCharacter(Character* character, const char* filename);

Character* loadCharacter(const char* filename);
#endif
