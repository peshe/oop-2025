/******************************************************/
/* Примерен код към курса ООП, ФМИ (2025)
*  Пример за различни операции с текстови файлове     
*   - Съхранение и четене на масив;
*   - Работа с командни аргументи и прости операции   */
/******************************************************/

#include <iostream>
#include <fstream>
#include <cstdlib>

int processArgs(char command, const char* file);

struct array
{
    size_t size;
    float* data;
};

bool validArray(const array& a)
{
    return a.data;
}

array createArray(size_t size)
{
    array result{ size, new(std::nothrow) float[size]};
    return result;
}

float totalSum(const array& a)
{
    if (!validArray(a)) return 0;

    float s = 0;
    for (size_t i = 0; i < a.size; ++i)
        s += a.data[i];
    return s;
}

void clearArray(array& a)
{
    delete[] a.data;
    a.data = nullptr;
}

// Генериране и запис на данни във текстов файл.
bool generateNumbersFile(const char* fileName, size_t size = 0)
{
    if (!fileName) {
        std::cerr << "Bad name!\n";
        return false;
    }
    if (size == 0) {
        size = rand() + 100;
    }
    
    std::ofstream file;
    file.open(fileName, std::ios::out);
    if (!file) {
        std::cerr << "Problem open " << fileName << "!\n";
        return false;
    }

    file << size << '\n';
    for (size_t ind = 0; ind < size; ++ind) {
        float elem = (float)rand()/RAND_MAX;
        elem *= rand();
        file << elem << ' ';
    }

    if (!file) {
        std::cerr << "Problem writing data to " << fileName << "!\n";
        return false;
    }
    file.close();
    return file.good();
}

array readAllNumbers(const char* fileName)
{
    array result{ 0, nullptr };

    if (!fileName){
        return result;
    }

    std::ifstream file(fileName, std::ios::in);
    if (!file) {
        std::cerr << "Error open " << fileName << " for reading!\n";
        return result;
    }

    size_t size;
    file >> size;
    if (file) {
        result = createArray(size);
        if (validArray(result)) {
            for (size_t ind = 0; file.good() && ind < size; ++ind) {
                float f;
                if(!(file >> f)){
                    result.size = ind;  // ver 1
                    std::cerr << "Error reading data at " << ind << "!\n";
                }
                result.data[ind] = f;
            }
        }
/*
        // ver2
        if (!file) {
            clearArray(result);
        }
*/
    }
    return result;
}

bool generateNumbersFile2(const char* fileName, size_t size = 0)
{
    if (!fileName) {
        std::cerr << "Bad name!\n";
        return false;
    }
    if (size == 0) {
        size = rand() + 100;
    }

    std::ofstream file;
    file.open(fileName, std::ios::out);
    if (!file) {
        std::cerr << "Problem open " << fileName << "!\n";
        return false;
    }
    for (size_t ind = 0; ind < size; ++ind) {
        float elem = (float)rand() / RAND_MAX;
        elem *= rand();
        file << elem << ' ';
    }

    if (!file) {
        std::cerr << "Problem writing data to " << fileName << "!\n";
        return false;
    }
    file.close();
    return file.good();
}

array readAllNumbers2(const char* fileName)
{
    array result{ 0, nullptr };

    if (!fileName) {
        return result;
    }

    std::ifstream file(fileName, std::ios::in);
    if (!file) {
        std::cerr << "Error open " << fileName << " for reading!\n";
        return result;
    }

    size_t size = 0;
    while (file) {
        float f;
        file >> f;
        size += file.good();
    }

    file.clear();
    file.close();
    file.open(fileName);

    if (file) {
        result = createArray(size);
        if (validArray(result)) {
            for (size_t ind = 0; file.good() && ind < size; ++ind) {
                float f;
                if (!(file >> f)) {
                    result.size = ind;
                    std::cerr << "Error reading data at " << ind << "!\n";
                }
                result.data[ind] = f;
            }
        }
/*
        // ver1
        if (!file) {
            clearArray(result);
        }
*/
    }
    return result;
}

int main(int argc, const char* argv[])
{
/*
    const char* numbersFile = "numbers.txt";
    if (generateNumbersFile2(numbersFile)) {
        std::cout << "Good! :)\n";
    }
    else {
        std::cout << "Not good! ;(\n";
    }
    array a = readAllNumbers2(numbersFile);
    if (validArray(a)) {
        std::cout << totalSum(a);
        clearArray(a);
    }
    else {
        std::cerr << "Bad array read.\n";
        return 1;
    }
*/
    if (argc < 2 || argv[1][0] != '-') {
        std::cerr << "Usage:\n"
            << argv[0] << " [<command>] <file>\n";
        return 1;
    }

    return processArgs(argv[1][1], argv[2]);
    return 0;
}


int countChars(const char* fileName);
int countWords(const char* fileName);
int countLines(const char* fileName);
void printHelp();

int processArgs(char command, const char* file)
{
    switch (command) {
    case 'c':
        return countChars(file);
    case 'l':
        return countLines(file);
    case 'w':
        return countWords(file);
    case 'h':
        printHelp();
        return 0;
    default:
        printHelp();
        return 1;
    }
}

void printHelp()
{
    std::cout << "Available commands:\n"
        "\t-c\tcounts chars in the file.\n"
        "\t-w\tcounts words in the file.\n"
        "\t-l\tcounts lines in the file.\n"
        "\t-h\tprints this help message.\n";
}

int countChars(const char* fileName)
{
    std::ifstream file(fileName, std::ios::in);
    if (!file) return -1;
    size_t count = 0;

    while (file.get() != EOF) {
        ++count;
    }
    std::cout << "Number of chars: " << count << std::endl;
    return 0;
}

int countWords(const char* fileName)
{
    std::ifstream file(fileName, std::ios::in);
    if (!file) return -1;
    size_t count = 0;
    char ch;
    while (file.get(ch)) {
        if (!isspace(ch)) {
            ++count;
            while (file && !isspace(file.get()))
                ;
        }
    }
    std::cout << "Number of words: " << count << std::endl;
    return 0;
}

int countLines1(const char* fileName)
{
    std::ifstream file(fileName, std::ios::in);
    if (!file) return -1;
    size_t count = 0;
    char ch;
    while (file.get(ch)) {
        count += ch == '\n';
    }
    std::cout << "Number of lines: " << count << std::endl;
    return 0;
}

int countLines(const char* fileName)
{
    std::ifstream file(fileName, std::ios::in);
    if (!file) return -1;
    size_t count = 0;

    const int BUFF_LEN = 1024;
    char buffer[1024];
    while (!file.eof()) {
        if (!file.bad()) file.clear();
        file.getline(buffer, BUFF_LEN);
        if (file) ++count;
        else if (file.eof()){
            count += file.gcount() > 0;
        }
    }
    std::cout << "Number of lines: " << count << std::endl;
    return 0;
}
