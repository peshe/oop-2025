/*
 Petar Armyanov  @ FMI 2025

 Enum data type.
*/

#include <iostream>
using std::cout;
using std::endl;

enum
{
    BEGIN,
    ONE,
    TWO,
    FIVE = 5,
    SIX,
    ZERO = 0
};

void print()
{
    cout << ZERO << " " << ONE << " "
         <<  TWO << " " << SIX << endl;
}

enum ColorType
{
    C_UNKNOWN = -1,
	C_BLACK,
    C_RED,
    C_GREEN,
    C_PINK,
    C_BROWN,
    C_BLUE,
    C_WHITE,
    C_GRAY,
    C_COUNTER
};

const char* const names[C_COUNTER] =
{
    "Black",
    "Red",
    "Green",
    "Pink",
    "Brown",
    "Blue",
    "White",
    "Gray"
};

void printColor(ColorType c)
{
    if (c < C_COUNTER && c > C_UNKNOWN)
        cout << names[c] << " ";

    switch (c)
    {
        case C_BLACK:   cout << c << " Cherno" << " " << names[c] << endl; break;
        case C_BLUE:    cout << c << " Sinjo" << " " << names[c]<< endl; break;
        case C_GREEN:   cout << c << " Zeleno" << " " << names[c]<< endl; break;
        case C_RED:     cout << c << " Cherveno" << " " << names[c]<< endl; break;
        case C_WHITE:   cout << c << " Bjalo" << " " << names[c]<< endl; break;
        case C_PINK:    cout << c << " Rozowo" << " " << names[c]<< endl; break;
        case C_GRAY:    cout << c << " Sivo" << " " << names[c]<< endl; break;
        default:        cout << c << " Neizvestno" << endl;

        case C_UNKNOWN:     // To suppress warning -switch-enum
        case C_COUNTER: break;
    }
}

void testCounting()
{
    for (int c = C_UNKNOWN+1; c < C_COUNTER; ++c)
        printColor((ColorType)c);
}

int main()
{
//    print();
//    testCounting();
    printColor(C_WHITE);
    ColorType c = C_WHITE;
    int col = 6;
    printColor((ColorType)6);
//    printColor((ColorType)100);
    return 0;
}
