#include <iostream>
#include <fstream>

namespace GlobalConstants {
    constexpr char NEW_LINE = '\n';
    constexpr char FILE_NAME[] = "file.txt";
}

unsigned int countCharFilestream(std::ifstream &file, char key) {
    if (!file) {
        std::cerr << "Invalid argument for input file stream!" << std::endl;
        return 0;
    }

    unsigned int count = 0;
    while (file) {
        if (file.get() == key) {
            count++;
        }
    }
    return count;
}

int main() {
    std::ifstream file(GlobalConstants::FILE_NAME);
    if (!file.is_open()) {
        std::cerr << "Error opening file!" << std::endl;
        return 1;
    }

    std::cout << countCharFilestream(file, GlobalConstants::NEW_LINE) + 1 << std::endl;

    file.close();
}
