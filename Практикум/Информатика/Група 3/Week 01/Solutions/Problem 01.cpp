#include <limits>

#include <iostream>



const int NUMBER1 = 3;
const int NUMBER2 = 5;
const int NUMBER3 = 7;




unsigned long long int readLimit();




unsigned long long int findSumMultiple(unsigned long long int limit, unsigned long long int number);



unsigned long long int findSumMultiples(unsigned long long int limit);



int main() {
    unsigned long long int limit = readLimit();

    std::cout << "The sum of the multiples of 3, 5, 7 is: " << findSumMultiples(limit) << std::endl;

    return 0;
}



unsigned long long int readLimit() {
    unsigned long long int limit = 0;

    while (limit < 2) {
        std::cout << "Enter the limit: ";

        std::cin >> limit;

        if (std::cin.fail()) {
            std::cin.clear  ();
            std::cin.ignore (std::numeric_limits<std::streamsize>::max(), '\n');
        } else {
            std::cin.clear  ();
            std::cin.ignore (std::numeric_limits<std::streamsize>::max(), '\n');

            return limit;
        }
    }

    return limit;
}



unsigned long long int findSumMultiple(unsigned long long int limit, unsigned long long int number) {
    limit = (limit - limit % number) / number;
    return number * limit * (limit + 1) / 2;
}



unsigned long long int findSumMultiples(unsigned long long int limit) {
    return  findSumMultiple(limit, NUMBER1)                     +
            findSumMultiple(limit, NUMBER2)                     +
            findSumMultiple(limit, NUMBER3)                     -
            findSumMultiple(limit, NUMBER1 * NUMBER2)           -
            findSumMultiple(limit, NUMBER2 * NUMBER3)           -
            findSumMultiple(limit, NUMBER3 * NUMBER1)           +
            findSumMultiple(limit, NUMBER1 * NUMBER2 * NUMBER3) ;
}



// warning: ISO C++ 1998 does not support `long long` [-Wlong-long]
