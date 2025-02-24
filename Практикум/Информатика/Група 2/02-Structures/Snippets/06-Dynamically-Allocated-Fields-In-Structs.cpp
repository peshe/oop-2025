#include <iostream>

struct Employee {
    char* name{};
    int age{};
    double wage{};
};

bool initializeEmployee(Employee& employee, const char* name, int age, double wage);
void printEmployee(const Employee& employee);
void freeEmployee(Employee& employee);

int main() {
    Employee employee;

    if (!initializeEmployee(employee, "John Doe", 25, 1000.0)) {
        return 1;
    }
    printEmployee(employee);
    freeEmployee(employee);

    Employee* dynamicEmployee = new (std::nothrow) Employee;

    if (dynamicEmployee == nullptr) {
        std::cout << "Failed to allocate memory for dynamicEmployee" << std::endl;

        return 1;
    }

    if (!initializeEmployee(*dynamicEmployee, "Jane Doe", 30, 2000.0)) {
        delete dynamicEmployee;
        dynamicEmployee = nullptr;

        return 1;
    }

    printEmployee(*dynamicEmployee);

    freeEmployee(*dynamicEmployee); // IMPORTANT: First free the dynamically allocated fields
    delete dynamicEmployee;         // IMPORTANT: Then free the struct itself
    dynamicEmployee = nullptr;

    return 0;
}

bool initializeEmployee(Employee& employee, const char* name, int age, double wage) {
    employee.name = new (std::nothrow) char[strlen(name) + 1];

    if (employee.name == nullptr) {
        std::cout << "Failed to allocate memory for employee name" << std::endl;

        return false;
    }

    strcpy(employee.name, name);

    employee.age = age;
    employee.wage = wage;

    return true;
}

void printEmployee(const Employee& employee) {
    std::cout << "Name: " << employee.name << std::endl;
    std::cout << "Age: " << employee.age << std::endl;
    std::cout << "Wage: " << employee.wage << std::endl;
}

void freeEmployee(Employee& employee) {
    delete[] employee.name;
    employee.name = nullptr;
}
