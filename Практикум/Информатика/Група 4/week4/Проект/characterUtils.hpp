#include "Character.hpp"
#ifndef CHARACTER_UTILS_HPP
#define CHARACTER_UTILS_HPP
// bool writeCharacterBinaryWithDynamicSize(const char *filename, Character *ch);
bool writeCharacterBinaryWithFixedSize(const char *filename, Character *ch);
Character *loadCharacterFixedSize(const char *filename);
// bool writeCharacterBinaryWithDynamicSizeOpenStream(std::ofstream &ofStr, Character *ch);
#endif