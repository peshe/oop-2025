#include <fstream>
#include <iostream>
#include <memory>

const size_t MAX_FILENAME = 40;

struct File
{
    char filename[MAX_FILENAME];
    size_t filesize;
    std::fstream stream;
};

File* openFile() {
    File* file = new(std::nothrow) File;
    
    if (file == nullptr) {
        return nullptr;
    }

    //std::cin.getline(file->filename, MAX_FILENAME);
    strcpy(file->filename, "jokes.csv");

    file->stream.open(file->filename);

    if (!file->stream.is_open() || file->stream.bad()) {
        return nullptr;
    }

    file->stream.seekg(0, std::ios_base::end);
    file->filesize = file->stream.tellg();
    file->stream.seekg(0, std::ios_base::beg);

    return file;
}

void closeFile(File*& file) {
    if (file == nullptr) {
        return;
    }
    
    if (file->stream.is_open()) {
        file->stream.close();
    } 

    delete file;
    file = nullptr;
}

char* readFile(File* file) {
    if (file == nullptr) {
        return nullptr;
    }

    char* data = new(std::nothrow) char[file->filesize]; 
    
    if (data == nullptr) {
        return nullptr;
    }

    if (!file->stream.is_open() && file->stream.bad()) {
        return nullptr;
    }

    file->stream.read(data, file->filesize);
    
    return data;
}

size_t countNChars(char* data, size_t n, char countable){
    if (data == nullptr) {
        return 0;
    }

    size_t count = 0;

    for (size_t i = 0; data[i] && i < n; i++)
    {
        count += (data[i] == countable)?1:0;
    }

    return count;
}
char** splitNAt(char* string, size_t n, char delim, size_t m) {
    char** delimsList = new(std::nothrow) char*[m];

    if (delimsList == nullptr) {
        return nullptr;
    }

    size_t countedDelims = 0;  
    size_t currLocation = 0;  
    size_t pastLocation = 0;

    while (countedDelims < m) {
        if (currLocation >= n) {
            break;
        }
        if (string[currLocation] == delim){
            delimsList[countedDelims] = strndup(string+pastLocation, currLocation-pastLocation);
            pastLocation = currLocation+1;
            countedDelims++;
        }
        ++currLocation;
    }

    return delimsList;
}

struct CSVformat{
    char** titles;
    char*** rows;
    char*** _original;
    size_t rowsSize;
    size_t colsSize;
};

char*** createWordMatrix(File* file, char* data, size_t lines, size_t delim, char delim2) {

    char** linesList = splitNAt(data, file->filesize, '\n', lines);

    char*** linesDelimList = new (std::nothrow)char**[lines];

    if (linesDelimList == nullptr) {
        return nullptr;
    }

    for (size_t i = 0; i < lines; i++)
    {
        linesDelimList[i] = splitNAt(linesList[i], file->filesize, delim2, delim+1);
    }
    for (size_t i = 0; i < lines; i++)
    {
        delete[] linesList[i];
    }
    
    delete[] linesList;

    return linesDelimList;
}

CSVformat* createCSVformat(File* file, char* data) {
    CSVformat* format = new(std::nothrow) CSVformat;
    if (format == nullptr) {
        std::cout << "Unable to allocate storage" << std::endl;
        return nullptr;
    }

    char delim3 = ',';

    // Тук може и да се направи във една функция, но реално сложноста си остава същата. 
    size_t delim = countNChars(data, file->filesize, delim3);
    size_t lines = countNChars(data, file->filesize, '\n');

    delim /= lines;

    char*** linesDelimList = createWordMatrix(file, data, lines, delim, delim3);

    format->titles = linesDelimList[0];
    format->rows = linesDelimList+1;
    format->_original = linesDelimList;
    format->rowsSize = lines;
    format->colsSize = delim+1;

    return format;
}

char** findUser(CSVformat* format, const char* user){
    size_t userIndex = 1; // може да се намери и динамично базирано
                          //  на format->titles 
    for (size_t i = 0; i < format->rowsSize-1; i++)
    {
        if (!strncmp(format->rows[i][1]+1, user, 100)){
            return format->rows[i];
        }
    }
    return nullptr;
}

// 9та става като сортирате имената лексикографски с някой от изучените от вас
// алгоритми за сортиране, и после ползвате binary search.

int main(int argc, char const *argv[])
{
    File* file = openFile();
    char* data = readFile(file);
    
    CSVformat* format = createCSVformat(file, data);

    for (size_t i = 0; i < format->colsSize; i++)
    {
        std::cout << format->titles[i];
    }
    std::cout << std::endl << "-------------------------" << std::endl;
    

    for (size_t i = 0; i < format->rowsSize-1; i++)
    {
        for (size_t j = 0; j < format->colsSize; j++)
        {
            std::cout << format->rows[i][j] << "$";
        }
        std::cout << "\n###"<<std::endl;;
        
    }
    
    std::cout << findUser(format, "Masai Graham")[3] << std::endl;

    delete[] data;
   

    for (size_t i = 0; i < format->rowsSize; i++)
    {
        for (size_t j = 0; j < format->colsSize; j++)
        {
            delete[] format->_original[i][j];
        }
        
        delete[] format->_original[i];
    }
    delete[] format->_original;

    closeFile(file);
    return 0;
}
