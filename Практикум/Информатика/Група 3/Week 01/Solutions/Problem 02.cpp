#include <limits>

#include <cassert>

#include <iostream>



#define MAX 1024



unsigned int readShift();



char*   buildString(                );
void    clearString(char*& string   );



bool    isLowerLetter(const char c);
bool    isUpperLetter(const char c);



void transformString(char* string, unsigned int shift);



int main() {
    unsigned int shift = readShift();


    char* string = buildString();

    if (string == nullptr) {
        std::cout << "Allocating Memory... ERROR!" << std::endl;

        return 1;
    }

    transformString(string, shift);
    std::cout << "The string is: " << string;

    clearString(string);


    return 0;
}



unsigned int readShift() {
    unsigned int shift = 0;

    while (true) {
        std::cout << "Enter the shift: ";

        std::cin >> shift;

        if (std::cin.fail()) {
            std::cin.clear  ();
            std::cin.ignore (std::numeric_limits<std::streamsize>::max(), '\n');
        } else {
            std::cin.ignore (std::numeric_limits<std::streamsize>::max(), '\n');
            return shift;
        }
    }
}



char* buildString() {
    char* string = new (std::nothrow) char[MAX];

    if (string != nullptr) {
        std::fputs("Enter the string: ",    stdout  );
        std::fgets(string, MAX,             stdin   );
    }

    return string;
}

void clearString(char*& string) {
    assert(string   !=  nullptr );

    delete[] string;

    string = nullptr;
}



bool isLowerLetter(const char c)    { return c >= 'a' && c <= 'z';  }
bool isUpperLetter(const char c)    { return c >= 'A' && c <= 'Z';  }



void transformString(char* string, unsigned int shift) {
    assert(string   !=  nullptr );

    while (*string != '\0') {
        if (isLowerLetter(*string)) {
            *string = (*string - 'a' + shift % 26) % 26 + 'a';
        } else if (isUpperLetter(*string)) {
            *string = (*string - 'A' + shift % 26) % 26 + 'A';
        } else {
            *string = *string + 0;
        }

        string = string + 1;
    }
}
