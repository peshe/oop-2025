/******************************************************/
/* Примерен код към курса ООП, ФМИ (2025)
*  Пример за работа с двоични файлове:
*   четене, запис и промяна намясто (inplace) на числа*/
/******************************************************/

#include <fstream>
#include <iostream>
#include <cassert>
#include <cstdio>

void writeNumbers(const char* fileName, size_t count = 32)
{
    assert(fileName);
    std::ofstream file(fileName, std::ios::out | std::ios::binary);
    if (!file) {
        std::cerr << "Problem open data file for writing!\n";
        return;
    }

    for (uint32_t num = 0; num < count; ++num) {
        file.write((const char*)&num, sizeof(num));
    }
    file.close();

    if (!file) {
        std::cerr << "Problem write data!\n";
        remove(fileName);
    }
}

void addNumbers(const char* fileName, size_t count = 10)
{
    assert(fileName);
    std::ofstream file(fileName, std::ios::in | std::ios::app | std::ios::binary);
    if (!file) {
        std::cerr << "Problem open data file for append!\n";
        return;
    }

    for (uint32_t num = 0; num < count; ++num) {
        file.write((const char*)&num, sizeof(num));
    }
    file.close();
    if (!file) {
        std::cerr << "Problem write data!\n";
    }
}

void printNumbers(const char* fileName)
{
    assert(fileName);
    std::ifstream file(fileName, std::ios::in | std::ios::binary);
    if (!file) {
        std::cerr << "Problem open data file!\n";
        return;
    }

    uint32_t number;
    while (file.read((char*)&number, sizeof(number))) {
        std::cout << number << ' ';
    }
    std::cout << '\n';
}

void changeNumbers(const char* fileName, unsigned div)
{
    assert(fileName);
    assert(div);

    std::fstream file(fileName, std::ios::in | std::ios::out | std::ios::binary);
    if (!file) {
        std::cerr << "Problem open data file!\n";
        return;
    }

    file.seekg(0, std::ios::end);
    size_t countNumbers = file.tellg()/sizeof(uint32_t);
    file.seekg(0);
    for (size_t ind = 0; ind < countNumbers; ++ind) {
        uint32_t num;
        file.read((char*) &num, sizeof(num));

        if (file && file.gcount() == sizeof(num)) {
            if (num % div == 0) {
                file.seekp((ind)*sizeof(num), std::ios::beg);
                num = 0;
                file.write((const char*)&num, sizeof(num));
                file.seekg(file.tellp());
            }
        }
        else { //partial data read...
            std::cerr << "Partial data read - unexpected! \n";
            return;
        }
    }
    file.close();
    printNumbers(fileName);

    //other way
    file.clear();
    file.open(fileName, std::ios::in | std::ios::out | std::ios::binary);
    uint32_t num;
    while (file.read((char*)&num, sizeof num)) {
        if (file.gcount() == sizeof num) {
            if (num == 0) {
                num = div;
                file.seekp((long long)file.tellg() - sizeof(num), std::ios::beg);
                file.write((const char*)&num, sizeof num);
                file.seekg(file.tellg());
            }
        }
        else {
            std::cerr << "Partial data read - unexpected! \n";
            return;
        }
    }
}

int main()
{
    const char* const name = "SomeData.dat";
    writeNumbers(name, 1000);
    printNumbers(name);
    addNumbers(name);
    printNumbers(name);
    changeNumbers(name, 5);
    printNumbers(name);
    return 0;
}

