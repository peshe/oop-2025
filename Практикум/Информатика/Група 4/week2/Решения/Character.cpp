#include <iostream>
#include <new>

#include "Weapon.hpp"
#include "Character.hpp"


Character* createCharacterWithParams(
    int life,
    int attack,
    char name[SIZE_NAME],
    Weapon* weapon) {
    Character* character = new (std::nothrow)Character;

    if (character == nullptr) {
        std::cout << "ERROR: allocating resources" << std::endl;
        return nullptr;
    }

    character->attackPower = attack;
    character->life = life;
    character->weapon = weapon;
    strncpy(character->name, name, SIZE_NAME);
    
    return character;
}

Character* createCharacter(Weapon* weapon) {
    int life;
    int attack;
    char name[SIZE_NAME];
    std::cout << "Enter character life:" << std::endl;
    std::cin >> life;
    std::cout << "Enter character attack:" << std::endl;
    std::cin >> attack;
    std::cin.ignore();
    std::cout << "Enter character name:" << std::endl;
    std::cin.getline(name, SIZE_NAME);
    return createCharacterWithParams(life, attack, name, weapon);
}

void freeCharacter(Character*& character) {
    if (character == nullptr) {
        std::cout << "Error: can not free empty character";
    }
    delete character;
    character = nullptr;
}

int getBonusSafe(Weapon* weapon){
    return (weapon==nullptr)?0:weapon->power;
}

int removeLife(Character*& charackter, Character*& charackter2) {
    charackter->life -= charackter2->attackPower*getBonusSafe(charackter2->weapon);
    return charackter->life;
}

void attack(Character* left, Character* right) {
    if (left == nullptr || right == nullptr)
    {
        std::cout << "ERROR: character" <<  ((left==nullptr) ? "left" : "right");
        std::cout << "is not alocated" << std::endl;
    }
    if (isDead(left) || isDead(right)){
        std::cout << ((isDead(left))? "Right ": "Left ");
        std::cout << "won congratulation!";
    }
    removeLife(left, right);
    removeLife(right, left);
}

bool isDead(Character* character) {
    if (character == nullptr)
    {
        std::cout << "ERROR: character is not alocated" << std::endl;
    }
    if (character->life <= 0) {
        return false;
    }
    return true;
}

