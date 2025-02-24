#include <iostream>

/* Bit fields
    * Bit fields are used to optimize memory usage.
    * They allow you to specify the number of bits that each member will occupy.
    * A bit field can be any integral type or enumeration type.
    * 
    * Bit fields are used in programs that must force a data structure to correspond to a fixed hardware representation and are unlikely to be portable.

    * Bitfields can only be used inside structured data types (struct, class, and union types).
        
    * The following restrictions apply to bit fields. You cannot:
        - Define an array of bit fields
        - Take the address of a bit field
        - Have a pointer to a bit field
        - Have a reference to a bit field

    * If a series of bit fields does not add up to the size of an int, padding can take place
*/
struct HalfByte {
    unsigned int lowNibble : 4; // 4 bits
    unsigned int highNibble : 4; // 4 bits
};

// You can use it to create flags, instead of using a full byte for each flag, you can use a single byte for multiple flags
struct Flags {
    unsigned int flag1 : 1; // 1 bit
    unsigned int flag2 : 1; // 1 bit
    unsigned int flag3 : 1; // 1 bit
    unsigned int flag4 : 1; // 1 bit
};

struct OnOff {
    unsigned light : 1;
    unsigned toaster : 1;
    int count;            /* 4 bytes */
    unsigned ac : 4;
    unsigned : 4;
    unsigned clock : 1;
    unsigned : 0;
    unsigned flag : 1;
};

int main() {
    HalfByte halfByte{ 0b1010, 0b0101 };

    std::cout << "Low nibble: " << halfByte.lowNibble << std::endl;
    std::cout << "High nibble: " << halfByte.highNibble << std::endl;
    std::cout << "Size of HalfByte: " << sizeof(HalfByte) << " bytes" << std::endl;

    std::cout << "---------------------------------" << std::endl;

    Flags flags{ 1, 0, 1, 0 };

    std::cout << "Flag 1: " << flags.flag1 << std::endl;
    std::cout << "Flag 2: " << flags.flag2 << std::endl;
    std::cout << "Flag 3: " << flags.flag3 << std::endl;
    std::cout << "Flag 4: " << flags.flag4 << std::endl;
    std::cout << "Size of Flags: " << sizeof(Flags) << " bytes" << std::endl;

    std::cout << "---------------------------------" << std::endl;

    std::cout << "Size of OnOff: " << sizeof(OnOff) << " bytes" << std::endl;


    return 0;
}
