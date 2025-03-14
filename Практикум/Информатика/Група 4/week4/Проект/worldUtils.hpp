#ifndef WORLD_UTILS_HPP
#define WORLD_UTILS_HPP
#include "World.hpp"
#include "Character.hpp"
bool saveWorldInBinaryNoDynamicMem(const char *filename, World *world);
// bool saveWorldInBinaryDynamicMem(const char *filename, World *world);
//  World *loadWorldFromBinaryDynamicMem(const char *filename);
bool removeDeadStatic(const char *filename);
// bool removeDeadDynamic(const char *filename);
bool insertAtPositionStatic(const char *filename, Character *character, int index);
bool changeAtIndexInBinary(const char *filename, size_t index, Character *ch);
World *loadWorldFixedSize(const char *filename);
#endif