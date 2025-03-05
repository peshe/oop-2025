#pragma once
#ifndef WEAPON_HPP
#define WEAPON_HPP

struct Weapon
{
    int power;
};

Weapon* createWeapon();
void freeWeapon(Weapon*& weapon);

// Бонус
Weapon* getWeapon(int index);

#endif
