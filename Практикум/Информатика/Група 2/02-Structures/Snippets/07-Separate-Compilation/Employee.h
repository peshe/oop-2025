/*
    * Separate Compilation
    *
    * Separate compilation is a technique that allows you to split your program into multiple files.
    * This is useful for large projects because it makes the code easier to manage and maintain.
    * In separate compilation, each file is compiled separately into an object file.
    * The object files are then linked together to create the final executable.
    * This allows you to make changes to one part of the program without having to recompile the entire program.
    * Separate compilation also makes it easier to reuse code in other projects.
    *
    * To use separate compilation, you need to create header files (.h) and source files (.cpp).
    * The header files contain the declarations of functions and variables, while the source files contain the definitions.
    * The header files are included in the source files using the #include directive.
    * The source files are compiled separately into object files using the compiler.
    * The object files are then linked together to create the final executable.
*/

/* #pragma once
    * #pragma once is a non-standard preprocessor directive that tells the compiler to include the file only once in a single compilation.
    * This prevents multiple inclusions of the same file, which can cause errors due to redefinitions of functions and variables.

    * #pragma once is supported by most modern compilers, but it is not part of the C++ standard.
    * If your compiler does not support #pragma once, you can use include guards instead.
    * Include guards are a standard way to prevent multiple inclusions of the same file..
*/
#pragma once

/*

Alternative to the #pragma once directive is the use of include guards:

#ifndef EMPLOYEE_H
#define EMPLOYEE_H
*/

/* Include guards
    * Include guards are a standard way to prevent multiple inclusions of the same file.
    * They are supported by all C++ compilers.

    * They use preprocessor directives such as #ifndef, #define, and #endif to check if the file has already been included.
    * The #ifndef directive checks if the token EMPLOYEE_H has been defined.
    * If it hasn't been defined, the code between #ifndef and #endif is included in the compilation.
    * The #define directive defines the token, and the #endif directive closes the block of code.
    * If the file has already been included, the code is skipped.
*/

// Relative path to the Date header file
#include "./Date/Date.h"

struct Employee {
    int id{};

    char* name{ nullptr };
    char* position{ nullptr };
    unsigned short age{};
    double salary{};
    Date hireDate{ 24, 2, 2025 };

    Employee* manager{ nullptr };
};

void initializeEmployee(Employee& employee, int id, const char* name, const char* position, unsigned short age, double salary, Employee* manager);
void initializeDynamicallyAllocatedEmployee(Employee*& employee, int id, const char* name, const char* position, unsigned short age, double salary, Employee* manager);
void printEmployee(const Employee& employee);
void freeEmployeeMembers(Employee& employee);
void freeEmployee(Employee*& employee);

/*
Use this if you want to use include guards instead of #pragma once:

#endif // EMPLOYEE_H

*/
