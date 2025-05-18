#include "Person.h"
#include "Employee.h"
#include "Stundet.h"

void printPerson(const Person& p)
{
    p.print();

    Person* ptr = p.clone();
    ptr->print();
    delete ptr;
}

int main()
{
    Person pesho("Pesho", 22);
    Employee sasho("Sasho", 33, 1500);
    
    /*printPerson(pesho);
    printPerson(sasho);
    printPerson(Employee("Ivan", 12, 25687));

    sasho.print();

    Employee* ptr = sasho.clone();

    ptr->getSalary();
    delete ptr;

    std::cout << pesho;
    std::cout << sasho;*/

    Manager ivan("Baj Ivan", 44, 1765);
    {
        Secretary ss(1234);
        ivan.hire(sasho);
        ivan.hire(ss);
    }
    ivan.print();

    Manager mp("Pesho", 12, 2222);
    mp.print();

    mp = ivan;
    mp.print();

    return 0;
}
