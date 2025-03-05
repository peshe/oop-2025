#pragma once
#ifndef WORLD_HPP
#define WORLD_HPP
#include <cstddef>

#include "Character.hpp"

struct World
{
    size_t numPeople;
    Character** people;
};

World* createWorld();

void freeWorld(World*& world);

void addCharacter(World* world, Character* charackter);

Character* mostPowerfull(World* world);

size_t cup(World* world);

#endif
