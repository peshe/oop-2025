#include <iostream>
#include "Bank.hpp"

void printDouble(const double number) {
    std::cout << number << std::endl;
}

void printInt(int number) {
    std::cout << number << std::endl;
}

int main() {
    ConversionRate c1{1, Currency::BGN, Currency::EUR};
    ConversionRate c2{2, Currency::BGN, Currency::EUR};
    ConversionRate c3{3, Currency::BGN, Currency::EUR};
    ConversionRate c4{4, Currency::BGN, Currency::EUR};
    ConversionRate c5{5, Currency::BGN, Currency::EUR};
    ConversionRate c6{6, Currency::BGN, Currency::EUR};
    const ConversionRate crates[] = {c1, c2, c3, c4, c5, c6};

    Client client1("One", "00000000001", Date(1, 1, 1970), Money(0, Currency::BGN));
    Client client2("Two", "00000000002", Date(1, 1, 1970), Money(0, Currency::BGN));

    Bank bank("Bank", crates);
    bank.addClient(client1);
    bank.addClient(client2);
    bank.deposit("0000000001", Money(20, Currency::BGN));

    std::cout << bank[1].getName() << std::endl;

    std::cout << "Hello World!" << std::endl;
    Money m1(200, Currency::BGN);
    Money m2(100, Currency::BGN);
    Money m3(0, Currency::UNKNOWN);

    std::cout << m1 << std::endl;
    std::cout << m1 + m2 << std::endl;
    std::cin >> m3;
    std::cout << m3 << std::endl;

    int amount2 = 2;
    std::cout << amount2 + m2 << std::endl;
    std::cout << m2 + amount2 << std::endl;
    std::cout << 3.14 + m2 << std::endl;

    printInt(m3);
    printDouble(m3);
    printDouble((double) m3);

    return 0;
}
