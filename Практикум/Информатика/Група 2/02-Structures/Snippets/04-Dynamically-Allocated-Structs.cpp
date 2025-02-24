#include <iostream>
#include <cstring>

#pragma warning(disable : 4996)

constexpr std::size_t kMaxNameLength = 100;

struct Employee {
    int id{};
    char name[kMaxNameLength]{};
    int age{};
    double wage{};

    Employee* boss{ nullptr }; // Pointer to another Employee struct
};

void printEmployee(const Employee& employee);

int main() {
    Employee boss{ 1, "Alice", 30, 2000.0 };

    Employee* employee = new (std::nothrow) Employee;

    if (employee == nullptr) {
        std::cout << "Failed to allocate memory" << std::endl;

        return 1;
    }

    /*
        C++ offers a member selection from pointer operator (->) (also sometimes called the arrow operator)
        that can be used to select members from a pointer to an object.

        This member selection from pointer operator (->) works identically to the member selection operator (.)
        but does an implicit dereference of the pointer object before selecting the member.
        Thus employee->id is equivalent to (*employee).id.
    */

    strcpy(employee->name, "John Doe"); // Access struct members using the arrow operator
    employee->id = 2; // Access struct members using the arrow operator
    (*employee).age = 25; // Access struct members using the dereference operator
    employee->wage = 1000.0; // Access struct members using the arrow operator
    employee->boss = &boss; // Access struct members using the arrow operator

    printEmployee(*employee);

    // Chaining the arrow operator
    std::cout << "Boss: " << employee->boss->name << std::endl;

    delete employee;
    employee = nullptr;

    return 0;
}

void printEmployee(const Employee& employee) {
    std::cout << "ID: " << employee.id << std::endl;
    std::cout << "Name: " << employee.name << std::endl;
    std::cout << "Age: " << employee.age << std::endl;
    std::cout << "Wage: " << employee.wage << std::endl;
}
