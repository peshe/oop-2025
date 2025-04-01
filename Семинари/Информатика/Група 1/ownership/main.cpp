#include <iostream>
#include "person.hpp"
#include "car.hpp"

int main()
{ 
    Person pesho(true, "Petar", "Petrov", "Petrov");
    Car myCar("Ford Ka");
    myCar.print();

    pesho.print();
    pesho.addNewCar(&myCar);
    pesho.print();
    myCar.print();

    Person pesho2(pesho);
    pesho2.print();
    pesho2.addNewCar(&myCar);
    pesho.print();
    pesho2.print();

    pesho2 = std::move(pesho);
    pesho2.print();
    
    {
        pesho = Person(true, "Marijka", "Petrova", "Ivanova");
        Car otherCar("Ferrari");
        pesho.addNewCar(&otherCar);
        pesho.print();
    }
    pesho.print();

    {
        Person someone(true);
        myCar.print();
        myCar.setOwner(&someone);
        myCar.print();
    }

    myCar.print();
    return 0;
}
