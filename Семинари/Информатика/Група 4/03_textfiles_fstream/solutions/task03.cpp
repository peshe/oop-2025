#include <cstring>
#include <iostream>
#include <fstream>

constexpr std::size_t MAX_WORD_LENGTH = 100;
constexpr char INPUT_FILENAME[] = "input.txt";
constexpr char RESULT_FILENAME[] = "result.txt";


void replaceWord(std::ifstream &source, std::ofstream &destination, char target[], char replacement[]) {
    if (!source || !destination) {
        std::cerr << "Error in replaceWord(): Invalid source or destination" << std::endl;
        return;
    }

    char buffer[MAX_WORD_LENGTH + 1];
    std::size_t bufferIndex = 0;
    while (source.good()) {
        char currentChar = source.get();
        // If the current char is whitespace, compare the buffer, output and reset index
        if (isspace(currentChar)) {
            buffer[bufferIndex] = '\0';
            if (std::strcmp(buffer, target) == 0) {
                destination << replacement;
            } else {
                destination << buffer;
            }
            destination << currentChar;

            bufferIndex = 0;
        } else {
            buffer[bufferIndex++] = currentChar;
        }
    }
}

int main() {
    std::ifstream inputFile(INPUT_FILENAME);
    if (!inputFile.is_open()) {
        std::cerr << "Error opening file for reading!" << std::endl;
        return 1;
    }

    std::ofstream outputFile(RESULT_FILENAME);
    if (!outputFile.is_open()) {
        std::cerr << "Error opening file for writing!" << std::endl;
        return 2;
    }
    replaceWord(inputFile, outputFile, "have", "HAVE");

    inputFile.close();
    outputFile.close();
}
