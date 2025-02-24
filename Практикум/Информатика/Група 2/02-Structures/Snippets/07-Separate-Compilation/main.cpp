#include <iostream>

// We include the header file to use the Employee struct and functions
#include "Employee.h"

/*
    Date.h is included in Employee.h, so we don't need to include it here.
    But we still include it to show that there are no issues with multiple inclusions.
    Because we have pragma once (or if we had include guards), the code in Date.h will be included only once.
*/
// Absolute path to the Date header file
#include "Date/Date.h"

int main() {
    Employee* ceo{ new Employee };
    Employee* manager{ nullptr };
    Employee employee{};

    initializeDynamicallyAllocatedEmployee(ceo, 1, "John Doe", "CEO", 50, 10000.0, nullptr);
    initializeDynamicallyAllocatedEmployee(manager, 2, "Jane Doe", "Manager", 30, 5000.0, ceo);
    initializeEmployee(employee, 3, "Alice", "Employee", 25, 2000.0, manager);

    ceo->hireDate = Date{ 1, 1, 2020 };

    printEmployee(*ceo);
    printEmployee(*manager);
    printEmployee(employee);

    freeEmployee(ceo);
    freeEmployee(manager);
    freeEmployeeMembers(employee);

    return 0;
}
