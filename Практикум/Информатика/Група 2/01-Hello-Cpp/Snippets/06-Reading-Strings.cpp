#include <iostream>
#include <cstring> // For C-style string functions
#include <cstdio>  // For std::fgets
#include <limits>  // For std::numeric_limits

int main() {
    // C-style string declaration
    char str[100];

    // Reading a C-style string using std::cin
    std::cout << "Enter a string (using std::cin): ";
    std::cin >> str;
    std::cout << "You entered: " << str << std::endl;

    // Clearing the input buffer to avoid issues with subsequent input
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    // Most times "std::cin.ignore()" will be enough. But if you want to clear the buffer completely, you can use the following:

    /* Reading a C-style string using std::fgets
        * std::fgets reads a line of text from the input stream
        * Reads until it encounters a newline ('\n') or until it has read n-1 characters, where n is the size of the buffer.
        * Retains the newline in the output buffer if there is space.
        * Returns a pointer to the buffer if successful, or nullptr if an error occurs or end-of-file is reached before any characters are read.
    */
    std::cout << "Enter another string (using std::fgets): ";
    std::fgets(str, sizeof(str), stdin);
    // Remove the newline character if present
    str[strcspn(str, "\n")] = '\0';
    std::cout << "You entered: " << str << std::endl;

    // Dynamic memory allocation for C-style strings
    char* dynamicStr = new char[100];
    std::cout << "Enter a string (dynamically allocated): ";
    /* Reading a C-style string using std::fgets
        * std::cin.getline reads a line of text from the input stream
        * Reads characters until it hits a delimiter (by default '\n') or the specified limit is reached.
        * Discards the delimiter (i.e., the newline is not stored in the buffer).
        * Returns the stream (i.e., a reference to the std::istream), which allows you to check the stream’s state (e.g., using std::cin.fail()) to determine if an error occurred (such as exceeding the buffer size).
        * if the input exceeds the specified limit, the stream's failbit is set, which you can check for error handling.
        * Prefered in C++
    */
    std::cin.getline(dynamicStr, 100);
    std::cout << "You entered: " << dynamicStr << std::endl;

    // Freeing the dynamically allocated memory
    delete[] dynamicStr;

    return 0;
}