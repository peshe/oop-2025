#include <fstream>
#include "worldUtils.hpp"
#include "characterUtils.hpp"
// за функциите със static предполагаме, че структурата Character има само статични полета и фиксиран размер
// за динамичните предполагаме че name и wеapon са динамични
// променете ги за да пасват на вашата имплементация
bool saveWorldInBinaryNoDynamicMem(const char *filename, World *world)
{
    std::ofstream ofStr(filename, std::ios::binary);
    if (!ofStr.is_open())
    {
        return false;
    }
    ofStr.write(reinterpret_cast<char *>(&world->numPeople), sizeof(world->numPeople)); // записваме размера на хората за да знаем колко памет да заделим при прочитане
    for (size_t i = 0; i < world->numPeople; i++)
    {
        ofStr.write(reinterpret_cast<char *>(world->people[i]), sizeof(Character));
    }
    ofStr.close();
    return true;
}
World *loadWorldFixedSize(const char *filename)
{
    std::ifstream ifStr(filename, std::ios::binary);
    if (!ifStr.is_open())
    {
        return nullptr;
    }
    World *world = new World;
    ifStr.read(reinterpret_cast<char *>(&world->numPeople), sizeof(world->numPeople));
    world->people = new Character *[world->numPeople];
    for (size_t i = 0; i < world->numPeople; i++)
    {
        world->people[i] = new Character;
        ifStr.read(reinterpret_cast<char *>(world->people[i]), sizeof(Character));
    }
    ifStr.close();
    return world;
}
// bool saveWorldInBinaryDynamicMem(const char *filename, World *world)
// {
//     std::ofstream ofStr(filename, std::ios::binary);
//     if (!ofStr.is_open())
//     {
//         return false;
//     }
//     ofStr.write(reinterpret_cast<char *>(&world->numPeople), sizeof(world->numPeople)); // записваме размера на хората за да знаем колко памет да заделим за поинтърите при прочитане
//     for (size_t i = 0; i < world->numPeople; i++)
//     {
//         writeCharacterBinaryWithDynamicSizeOpenStream(ofStr, world->people[i]);
//     }
//     ofStr.close();
//     return true;
// }
// World *loadWorldFromBinaryDynamicMem(const char *filename)
// {
//     std::ifstream
//         ifStr(filename, std::ios::binary);
//     if (!ifStr.is_open())
//     {
//         return nullptr;
//     }
//     World *world = new World;
//     ifStr.read(reinterpret_cast<char *>(&world->numPeople), sizeof(world->numPeople));
//     world->people = new Character *[world->numPeople];
//     for (size_t i = 0; i < world->numPeople; i++)
//     {
//         world->people[i] = new Character;
//         size_t sizeOfName;
//         ifStr.read(reinterpret_cast<char *>(&sizeOfName), sizeof(sizeOfName));
//         world->people[i]->name = new char[sizeOfName];
//         ifStr.read(reinterpret_cast<char *>(world->people[i]->name), sizeof(char) * sizeOfName);
//         int weaponSize = sizeof(Weapon);
//         ifStr.read(reinterpret_cast<char *>(&weaponSize), sizeof(weaponSize));
//         world->people[i]->weapon = new Weapon;
//         ifStr.read(reinterpret_cast<char *>(world->people[i]->weapon), sizeof(Weapon));
//         ifStr.read(reinterpret_cast<char *>(&world->people[i]->life), sizeof(int));
//         ifStr.read(reinterpret_cast<char *>(&world->people[i]->attackPower), sizeof(int));
//     }
//     ifStr.close();
//     return world;
// }
bool removeDeadStatic(const char *filename)
{
    std::ifstream file(filename, std::ios::in | std::ios::binary);
    std::ofstream temp("temp.bin", std::ios::out | std::ios::binary);
    if (!file.is_open() || !temp.is_open())
    {
        return false;
    }
    size_t numPeople;
    size_t newNumPeople = 0;
    file.read(reinterpret_cast<char *>(&numPeople), sizeof(numPeople));
    temp.write(reinterpret_cast<char *>(&newNumPeople), sizeof(newNumPeople));
    for (size_t i = 0; i < numPeople; i++)
    {
        Character ch;
        file.read(reinterpret_cast<char *>(&ch), sizeof(Character));
        if (ch.life > 0)
        {
            temp.write(reinterpret_cast<char *>(&ch), sizeof(Character));
            newNumPeople++;
        }
    }
    temp.seekp(0, std::ios::beg);
    temp.write(reinterpret_cast<char *>(&newNumPeople), sizeof(newNumPeople));
    file.close();
    temp.close();
    std::remove(filename);
    std::rename("temp.bin", filename);
    return true;
}
// bool removeDeadDynamic(const char *filename)
// {
//     std::ifstream file(filename, std::ios::in | std::ios::binary);
//     std::ofstream temp("temp.bin", std::ios::out | std::ios::binary);
//     if (!file.is_open() || !temp.is_open())
//     {
//         return false;
//     }
//     size_t numPeople;
//     size_t newNumPeople = 0;
//     file.read(reinterpret_cast<char *>(&numPeople), sizeof(numPeople));
//     temp.write(reinterpret_cast<char *>(&newNumPeople), sizeof(newNumPeople));
//     for (size_t i = 0; i < numPeople; i++)
//     {
//         size_t sizeOfName;
//         file.read(reinterpret_cast<char *>(&sizeOfName), sizeof(sizeOfName));
//         Character ch;
//         ch.name = new char[sizeOfName];
//         file.read(reinterpret_cast<char *>(ch.name), sizeof(char) * sizeOfName);
//         int weaponSize = sizeof(Weapon);
//         file.read(reinterpret_cast<char *>(&weaponSize), sizeof(weaponSize));
//         ch.weapon = new Weapon;
//         file.read(reinterpret_cast<char *>(ch.weapon), sizeof(Weapon));
//         file.read(reinterpret_cast<char *>(&ch.life), sizeof(int));
//         file.read(reinterpret_cast<char *>(&ch.attackPower), sizeof(int));
//         if (ch.life > 0)
//         {
//             writeCharacterBinaryWithDynamicSizeOpenStream(temp, &ch);
//             newNumPeople++;
//         }
//     }
//     temp.seekp(0, std::ios::beg);
//     temp.write(reinterpret_cast<char *>(&newNumPeople), sizeof(newNumPeople));
//     file.close();
//     temp.close();
//     std::remove(filename);
//     std::rename("temp.bin", filename);
//     return true;
// }
bool insertAtPositionStatic(const char *filename, Character *character, int index)
{
    std::fstream fStr(filename, std::ios::out | std::ios::in | std::ios::binary);
    std::ofstream temp("temp.bin", std::ios::out | std::ios::binary);
    if (!fStr.is_open() || !temp.is_open())
    {
        return false;
    }
    size_t numPeople;
    fStr.read(reinterpret_cast<char *>(&numPeople), sizeof(numPeople));
    if (index >= numPeople)
    {
        fStr.seekp(0, std::ios::end);
        fStr.write(reinterpret_cast<char *>(character), sizeof(Character));
        numPeople++;
        fStr.seekp(0, std::ios::beg);
        fStr.write(reinterpret_cast<char *>(&numPeople), sizeof(numPeople));
        fStr.close();
        temp.close();
        return true;
    }

    numPeople++;
    temp.write(reinterpret_cast<char *>(&numPeople), sizeof(numPeople));
    for (size_t i = 0; i < numPeople; i++)
    {
        Character ch;
        if (i == index)
        {
            temp.write(reinterpret_cast<char *>(character), sizeof(Character));
        }
        else
        {
            fStr.read(reinterpret_cast<char *>(&ch), sizeof(Character));
            temp.write(reinterpret_cast<char *>(&ch), sizeof(Character));
        }
    }
    fStr.close();
    temp.close();
    std::remove(filename);
    std::rename("temp.bin", filename);
    return true;
}
bool changeAtIndexInBinary(const char *filename, size_t index, Character *ch)
{
    std::fstream fstr(filename, std::ios::in | std::ios::out | std::ios::binary);
    if (!fstr.is_open())
    {
        return false;
    }
    fstr.seekg(sizeof(size_t) + sizeof(Character) * index, std::ios::beg);
    fstr.write(reinterpret_cast<char *>(ch), sizeof(Character));
    fstr.close();
    return true;
}