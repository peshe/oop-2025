#include <cassert>

#include <cstring>

#include <limits>

#include <iostream>



#define MAX 1024

#define MAX_COLORS   4
#define MAX_VALUES  14



enum class Color {
    INVALID =   -1,
    CLUB    =    0,
    DIAMOND =    1,
    HEART   =    2,
    SPADE   =    3,
};

enum class Value : int /* char */{
    ZERO    =    0, // '0',
    ONE     =    1, // '1',
    TWO     =    2, // '2',
    THREE   =    3, // '3',
    FOUR    =    4, // '4',
    FIVE    =    5, // '5',
    SIX     =    6, // '6',
    SEVEN   =    7, // '7',
    EIGHT   =    8, // '8',
    NINE    =    9, // '9',
    TEN     =   10, // 'T',
    JACK    =   11, // 'J',
    QUEEN   =   12, // 'Q',
    KING    =   13, // 'K',
    ACE     =   14, // 'A',
};



const char* colors[5]   =   {
    "INVALID"   ,
    "CLUB"      ,
    "DIAMOND"   ,
    "HEART"     ,
    "SPADE"     ,
};



char*   buildString(                );
void    clearString(char*& string   );



int     getCorresponding(const char& letter);



Color   getColor(const char* string);
Value   getValue(const int & letter);



int compareColors(const Color& color1, const Color& color2);
int compareValues(const Value& value1, const Value& value2);



int main() {
    char* string1 = buildString();
    char* string2 = buildString();

    if (string1 == nullptr) {
        std::cout << "Allocating Memory... ERROR!" << std::endl;

        return 1;
    }

    if (string2 == nullptr) {
        std::cout << "Allocating Memory... ERROR!" << std::endl;

        clearString(string1);

        return 1;
    }

    char letter1 = 0;
    char letter2 = 0;

    std::cout << "Enter the value of the card: ";   std::cin >> letter1;
    std::cout << "Enter the value of the card: ";   std::cin >> letter2;


    Color color1 = getColor(string1);
    Color color2 = getColor(string2);

    Value value1 = getValue(getCorresponding(letter1));
    Value value2 = getValue(getCorresponding(letter2));


    clearString(string1);
    clearString(string2);


    if (compareColors(color1, color2) == 0) {
        if (compareValues(value1, value2) > 0) {
            std::cout << "Card 1 is stronger than Card 2!" << std::endl;
        } else if (compareValues(value1, value2) < 0) {
            std::cout << "Card 2 is stronger than Card 1!" << std::endl;
        } else {
            std::cout << "Card 1 is equal to the Card 2!" << std::endl;
        }
    } else {
        if (compareColors(color1, color2) > 0) {
            std::cout << "Card 1 is stronger than Card 2!" << std::endl;
        } else {
            std::cout << "Card 2 is stronger than Card 1!" << std::endl;
        }
    }


    return 0;
}



char* buildString() {
    char* string = new (std::nothrow) char[MAX];

    if (string != nullptr) {
        std::cout << "Enter the name of the card: ";

        std::cin.getline(string, MAX, '\n');
    }

    return string;
}

void clearString(char*& string) {
    assert(string   !=  nullptr );

    delete[] string;

    string = nullptr;
}



int getCorresponding(const char& letter) {
    if (letter >= '1' && letter <= '9') {
        return letter - '0';
    } else {
        switch (letter) {
            case 'T':   return 10;
            case 'J':   return 11;
            case 'Q':   return 12;
            case 'K':   return 13;
            case 'A':   return 14;
            default :   return  0;
        }
    }
}



Color getColor(const char* string) {    
    for (unsigned int i = 1; i < MAX_COLORS; ++i) {
        if (strcmp(string, colors[i]) == 0) {
            return static_cast<Color>(i);
        }
    }

    return Color::INVALID;
}

Value getValue(const int& letter) {
    if (letter < 1 || letter > 14) {
        return Value::ZERO;
    }

    return static_cast<Value>(letter);
}



int compareColors(const Color& color1, const Color& color2) {
    assert(color1 != Color::INVALID);
    assert(color2 != Color::INVALID);

    if (color1 < color2) {
        return -1;
    } else if (color1 > color2) {
        return 1;
    } else {
        return 0;
    }
}

int compareValues(const Value& value1, const Value& value2) {
    assert(value1 != Value::ZERO);
    assert(value2 != Value::ZERO);

    if (value1 < value2) {
        return -1;
    } else if (value1 > value2) {
        return 1;
    } else {
        return 0;
    }
}
