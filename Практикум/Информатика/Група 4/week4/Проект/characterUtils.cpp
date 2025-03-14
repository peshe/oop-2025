#include <fstream>
#include <string.h>
#include "characterUtils.hpp"
// за функциите със static предполагаме, че структурата Character има само статични полета и фиксиран размер
// за динамичните предполагаме че name и wеapon са динамични
// променете ги за да пасват на вашата имплементация
bool writeCharacterBinaryWithFixedSize(const char *filename, Character *ch)
{
    std::ofstream ofStr(filename, std::ios::app | std::ios::binary);
    if (!ofStr.is_open())
    {
        return false;
    }
    ofStr.write(reinterpret_cast<char *>(ch), sizeof(Character)); // в случая в character няма динамична памет
    ofStr.close();
    return true;
}
Character *loadCharacterFixedSize(const char *filename)
{
    std::ifstream ifStr(filename, std::ios::binary);
    if (!ifStr.is_open())
    {
        return nullptr;
    }
    Character *ch = new Character;
    ifStr.read(reinterpret_cast<char *>(ch), sizeof(Character));
    ifStr.close();
    return ch;
}
// bool writeCharacterBinaryWithDynamicSize(const char *filename, Character *ch)
// {
//     std::ofstream ofStr(filename, std::ios::app | std::ios::binary);
//     if (!ofStr.is_open())
//     {
//         return false;
//     }
//     bool res = writeCharacterBinaryWithDynamicSizeOpenStream(ofStr, ch);
//     ofStr.close();
//     return res;
// }
// bool writeCharacterBinaryWithDynamicSizeOpenStream(std::ofstream &ofStr, Character *ch)
// {
//     if (!ofStr.is_open())
//     {
//         return false;
//     }
//     size_t sizeOfName = strlen(ch->name) + 1; // +1 заради терминиращата нула
//     ofStr.write(reinterpret_cast<char *>(&sizeOfName), sizeof(sizeOfName));
//     ofStr.write(reinterpret_cast<char *>(ch->name), sizeof(char) * sizeOfName);
//     int sizeOfWeapon = sizeof(Weapon);
//     ofStr.write(reinterpret_cast<char *>(&sizeOfWeapon), sizeof(sizeOfWeapon));
//     ofStr.write(reinterpret_cast<char *>(ch->weapon), sizeof(Weapon));
//     ofStr.write(reinterpret_cast<char *>(&ch->life), sizeof(int));
//     ofStr.write(reinterpret_cast<char *>(&ch->attackPower), sizeof(int));
//     return true;
// }
