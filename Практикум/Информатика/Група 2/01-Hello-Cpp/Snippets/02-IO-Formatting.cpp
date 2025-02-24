#include <iostream>
#include <iomanip> // for std::setw, std::setfill, std::setprecision

int main() {
    // Example 1: Width and Fill
    // In C++:
    std::cout << "Width and Fill in C++:\n";
    std::cout << std::setw(10) << std::setfill('*') << 123 << std::endl; // Output: *******123
    // std::setw(10) sets the width of the next output to 10 characters
    // std::setfill('*') sets the fill character to '*'
    // These settings only affect the next output operation

    // Resetting width and fill
    std::cout << std::setw(0) << std::setfill(' '); // Reset to default

    // In C:
    printf("Width and Fill in C:\n");
    printf("%10d\n", 123); // Output:        123
    // In C, width is set using %10d in the format string
    // Fill character is always space by default

    // Example 2: Precision
    // In C++:
    std::cout << "Precision in C++:\n";
    std::cout << std::setprecision(5) << 123.456789 << std::endl; // Output: 123.46
    // std::setprecision(5) sets the precision of floating-point numbers to 5 digits
    // This setting affects all subsequent floating-point output

    // Resetting precision
    std::cout << std::setprecision(6); // Reset to default precision

    // In C:
    printf("Precision in C:\n");
    printf("%.5f\n", 123.456789); // Output: 123.45679
    // In C, precision is set using %.5f in the format string

    // Example 3: Fixed and Scientific Notation
    // In C++:
    std::cout << "Fixed and Scientific Notation in C++:\n";
    std::cout << std::fixed << 123.456789 << std::endl; // Output: 123.456789
    std::cout << std::scientific << 123.456789 << std::endl; // Output: 1.234568e+02
    // std::fixed sets the floating-point output to fixed-point notation
    // std::scientific sets the floating-point output to scientific notation
    // These settings affect all subsequent floating-point output

    // Resetting to default notation
    std::cout.unsetf(std::ios::fixed | std::ios::scientific); // Reset to default notation

    // In C:
    printf("Fixed and Scientific Notation in C:\n");
    printf("%f\n", 123.456789); // Output: 123.456789
    printf("%e\n", 123.456789); // Output: 1.234568e+02
    // In C, notation is set using %f for fixed and %e for scientific in the format string

    return 0;
}