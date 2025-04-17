#include <iostream>
#include "Bank.hpp"

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

    return 0;
}
