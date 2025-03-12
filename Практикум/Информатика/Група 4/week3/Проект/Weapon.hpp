#pragma once
#ifndef WEAPON_HPP
#define WEAPON_HPP

struct Weapon
{
    int power;
};

Weapon* createWeapon();
void freeWeapon(Weapon*& weapon);
Weapon* createWeaponWithParam(int param);

// Бонус
Weapon* getWeapon(int index);

void saveWeapon(Weapon* weapon, const char* filename);

Weapon* loadWeapon(const char* filename);

#endif
