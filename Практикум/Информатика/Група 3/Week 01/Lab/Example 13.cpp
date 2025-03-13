#include <cstdarg>

#include <iostream>



int min(const int argumentCount, ...);
int max(const int argumentCount, ...);



int main() {
    std::cout << "MIN Result 1: " << min(1, 1) << std::endl;
    std::cout << "MAX Result 1: " << max(1, 1) << std::endl;
    
    std::cout << "MIN Result 2: " << min(2, 3, 7) << std::endl;
    std::cout << "MAX Result 2: " << max(2, 3, 7) << std::endl;

    std::cout << "MIN Result 3: " << min(3, 7, 9, 13) << std::endl;
    std::cout << "MAX Result 3: " << max(3, 7, 9, 13) << std::endl;


    return 0;
}



int min(const int argumentCount, ...) {
    va_list arguments;

    va_start(arguments, argumentCount);

    int minNumber = va_arg(arguments, int);

    for (int i = 2; i <= argumentCount; ++i) {
        int buffer = va_arg(arguments, int);
        minNumber = (buffer < minNumber) ? buffer : minNumber;
    }

    va_end(arguments);

    return minNumber;
}

int max(const int argumentCount, ...) {
    va_list arguments;

    va_start(arguments, argumentCount);

    int maxNumber = va_arg(arguments, int);

    for (int i = 2; i <= argumentCount; ++i) {
        int buffer = va_arg(arguments, int);
        maxNumber = (buffer > maxNumber) ? buffer : maxNumber;
    }

    va_end(arguments);

    return maxNumber;
}
