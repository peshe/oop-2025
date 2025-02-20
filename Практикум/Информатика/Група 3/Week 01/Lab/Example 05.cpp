#include <iostream>



namespace NamespaceA {
    int i = 1;
}

namespace NamespaceB {
    int i = 3;
    int j = 7;
    int k = 9;

    namespace NamespaceB1 {
        int n = 1;
        int m = 3;
    }

    namespace NamespaceB2 {
        int n = 7;
        int m = 9;
    }

    using namespace NamespaceB1;
    using namespace NamespaceB2;

    // int number1 = n; Ambigious - NamespaceB1::n or NamespaceB2::n
    // int number2 = m; Ambigious - NamespaceB1::m or NamespaceB2::m

    int number1 = NamespaceB1::n;
    int number2 = NamespaceB2::n;
    int number3 = NamespaceB1::m;
    int number4 = NamespaceB2::m;
}



using namespace NamespaceA;
using namespace NamespaceB;



int main() {
    std::cout << "Namespace A, I: " << NamespaceA::i << std::endl;

    std::cout << "Namespace B, I: " << NamespaceB::i << std::endl;
    std::cout << "Namespace B, J: " << NamespaceB::j << std::endl;
    std::cout << "Namespace B, K: " << NamespaceB::k << std::endl;

    std::cout << "Namespace B1, N: " << NamespaceB::NamespaceB1::n << std::endl;
    std::cout << "Namespace B1, M: " << NamespaceB::NamespaceB1::m << std::endl;
    std::cout << "Namespace B2, N: " << NamespaceB::NamespaceB2::n << std::endl;
    std::cout << "Namespace B2, M: " << NamespaceB::NamespaceB2::m << std::endl;

    std::cout << "Namespace B, Number 1: " << NamespaceB::number1 << std::endl;
    std::cout << "Namespace B, Number 2: " << NamespaceB::number2 << std::endl;
    std::cout << "Namespace B, Number 3: " << NamespaceB::number3 << std::endl;
    std::cout << "Namespace B, Number 4: " << NamespaceB::number4 << std::endl;

    return 0;
}
