#include <iostream>

/* Enum (Traditional)
    - Decalred using the keyword enum

    - By default, the underlying type is an integer, 
        and the enumerators are automatically assigned successive integer values starting at 0 (unless specified otherwise).

    - Traditional enums can implicitly convert to their underlying integer type, which can sometimes lead to type-safety issues.

    - The enumerators (Monday, Tuesday, Wednesday, ...) are introduced into the surrounding scope, which can cause naming conflicts.
        Meaning, if you have another variable named Monday, it will cause a conflict.
*/
enum Day {
    Monday,
    Tuesday,
    Wednesday,
    Thursday,
    Friday,
    Saturday,
    Sunday
};

/* Scoped Enum (Enum Class)
    - Introduced in C++11 to address the issues with traditional enums.

    - Declared using the keyword enum class

    - Enum classes are strongly typed, meaning that the enumerators are not implicitly converted to an integer type.
        If you want to use the enumerator as an integer, you must explicitly cast it.

    - Enum classes are scoped, meaning that the enumerators are only visible within the enum class and
        must be accessed using the scope resolution operator (::).

    - Enum classes are the preferred way to define enums in modern C++ code.

    - You can specify an underlying type for scoped enums if needed (As shown below).
*/
enum class Color : char { // Specify the underlying type of the enum
    Red = 'r', // You can specify the value of the enumerator
    Green = 'g',
    Blue = 'b'
};

int main() {
    // Using the simple enum
    Day today = Wednesday;
    if (today == Wednesday) {
        std::cout << "Today is Wednesday." << std::endl;
    }

    // Using the enum class
    Color favoriteColor = Color::Blue;
    if (favoriteColor == Color::Blue) {
        std::cout << "Favorite color is Blue." << std::endl;
    }

    // Enum class requires scope resolution to access the enumerators
    // This prevents name conflicts with other parts of the code
    // For example, the following line would cause a compilation error if Color was a simple enum:
    // if (favoriteColor == Blue) { ... }

    return 0;
}