#include "Interval.hpp"

int main(int argc, const char* argv[]) {

    Interval t1(3, 10); // [3, 10]
    Interval t2(4, 14); // [4, 14]
    Interval t3; // [0, 0]

    Interval result = t1.intersect(t2); // [4, 10]

    t2.isSuperInterval(result); //true

    result.calcPrimeNumbersInTheInterval() // 2 (only 5 and 7)

    return 0;
}