#include "vector.hpp"
using namespace fmi::oop;

int main()
{
    Vector V1(1);
    Vector V2(V1);
    Vector V3 = V1 + V2;

    V1[0] = 2;
    std::cout << V1 << std::endl;
    --V1;
    std::cout << V1 << std::endl;

    --V1;
    std::cout << V1 << std::endl;
    
    std::cout << (const char*)V3 << std::endl;

    V3[0] = 1;
    V3 += 3;

    for (const double* elem = V3.begin(); elem != V3.end(); ++elem) {
        std::cout << *elem << ' ';
    }
    std::cout << std::endl;

    for (double d : V3) {
        std::cout << d << ' ';
    }
    std::cout << std::endl;
    
    return 0;
}
