#include <iostream>
#include <fstream>
#include <cstdint>
#include <climits>
#include <cstring>

void encode(std::uint8_t byte, std::uint8_t* res)
{
    std::memset(res, 0, 2*sizeof(byte));
    for(int i = CHAR_BIT-1; i>=0; i--)
    {
        *res <<= 2;
        *res |= ((byte>>i)&1)? 0b10: 0b01;
        if(i % (CHAR_BIT/2) == 0)
            res++;
    }
}

void encode(std::ifstream& ifs, std::ofstream& ofs)
{
    uint8_t byte;
    while(ifs.read((char*)&byte, sizeof(byte)))
    {
        uint8_t res[2];
        encode(byte, res);
        ofs.write((const char*)&res, sizeof(res));
    }
}

int main()
{
    std::ifstream ifs;
    ifs.open("input.bin", std::ios::binary);
    if(!ifs)
    {
        std::cerr << "could not open input.bin\n";
        return 1;
    }

    std::ofstream ofs;
    ofs.open("output.bin", std::ios::binary);
    if(!ofs)
    {
        std::cerr << "could not open output.bin\n";
        ifs.close();
        return 1;
    }

    encode(ifs, ofs);
    ifs.close();
    ofs.close();
    return 0;
}