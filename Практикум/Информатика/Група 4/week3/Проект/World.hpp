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

void saveWorld(World* world, const char* filename);

World* loadWorld(const char* filename);

// 8. Трябва да пазите героите в лексикографски сортиран вид по името.
//      И после трябва да ползвате двоично търсене

#endif
