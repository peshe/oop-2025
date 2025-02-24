#include "Employee.h"

#include <iostream>
#include <iomanip>
#include <cstring>

#pragma warning(disable : 4996)

void initializeEmployee(Employee& employee, int id, const char* name, const char* position, unsigned short age, double salary, Employee* manager) {
    employee.name = new (std::nothrow) char[strlen(name) + 1];
    if (employee.name == nullptr) {
        std::cout << "Failed to allocate memory for employee name!" << std::endl;

        return;
    }

    strcpy(employee.name, name);

    employee.position = new (std::nothrow) char[strlen(position) + 1];
    if (employee.position == nullptr) {
        std::cout << "Failed to allocate memory for employee position!" << std::endl;

        freeEmployeeMembers(employee);

        return;
    }

    strcpy(employee.position, position);

    employee.id = id;
    employee.age = age;
    employee.salary = salary;
    employee.manager = manager;
}

void initializeDynamicallyAllocatedEmployee(Employee*& employee, int id, const char* name, const char* position, unsigned short age, double salary, Employee* manager) {
    if (employee == nullptr) {
        employee = new (std::nothrow) Employee;

        if (employee == nullptr) {
            std::cout << "Failed to allocate memory for employee!" << std::endl;

            return;
        }
    }

    employee->id = id;
    employee->age = age;
    employee->salary = salary;
    employee->manager = manager;

    employee->name = new (std::nothrow) char[strlen(name) + 1];
    if (employee->name == nullptr) {
        std::cout << "Failed to allocate memory for employee name!" << std::endl;

        freeEmployee(employee);

        return;
    }

    strcpy(employee->name, name);

    employee->position = new (std::nothrow) char[strlen(position) + 1];

    if (employee->position == nullptr) {
        std::cout << "Failed to allocate memory for employee position!" << std::endl;

        freeEmployee(employee);

        return;
    }

    strcpy(employee->position, position);
}

void printEmployee(const Employee& employee) {
    std::cout << std::setw(25) << std::setfill('-') << '\n';
    std::cout << std::setw(0) << std::setfill(' ');

    std::cout << "Employee Data:" << std::endl;
    std::cout << "ID: " << employee.id << std::endl;
    std::cout << "Name: " << employee.name << std::endl;
    std::cout << "Age: " << employee.age << std::endl;
    std::cout << "Salary: " << employee.salary << std::endl;
    std::cout << "Position: " << employee.position << std::endl;
    std::cout << "Hired on: "; printDate(employee.hireDate); std::cout << std::endl;
    std::cout << "Manager: " << (employee.manager ? employee.manager->name : "No manager") << std::endl;

    std::cout << std::setw(25) << std::setfill('-') << '\n';
    std::cout << std::setw(0) << std::setfill(' ');
}

void freeEmployeeMembers(Employee& employee) {
    if (employee.name != nullptr) {
        delete[] employee.name;
        employee.name = nullptr;
    }

    if (employee.position != nullptr) {
        delete[] employee.position;
        employee.position = nullptr;
    }
}

void freeEmployee(Employee*& employee) {
    if (employee == nullptr) {
        return;
    }

    freeEmployeeMembers(*employee);

    delete employee;
    employee = nullptr;
}
