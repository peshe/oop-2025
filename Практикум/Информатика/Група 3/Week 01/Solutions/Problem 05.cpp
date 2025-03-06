#include <limits>

#include <cassert>

#include <iostream>



int             readNumb(                   );
unsigned int    readSize(const char* string );



int**   buildMatrix(                            unsigned int rows, unsigned int cols);
void    clearMatrix(            int**&  matrix, unsigned int rows                   );

void    inputMatrix(            int**   matrix, unsigned int rows, unsigned int cols);
void    printMatrix(const int* const*   matrix, unsigned int rows, unsigned int cols);



void transposeMatrix(const int* const* matrix, unsigned int rows, unsigned int cols);



int main() {
    unsigned int rows   =   readSize("ROWS");
    unsigned int cols   =   readSize("COLS");


    int** matrix = buildMatrix(rows, cols);

    if (matrix == nullptr) {
        std::cout << "Allocating Memory... ERROR!" << std::endl;

        return 1;
    }


    inputMatrix(matrix, rows, cols);
    printMatrix(matrix, rows, cols);


    transposeMatrix(matrix, rows, cols);


    clearMatrix(matrix, rows);


    return 0;
}



int readNumb() {
    int number = 0;

    while (true) {
        std::cin >> number;

        if (std::cin.fail()) {
            std::cin.clear  ();
            std::cin.ignore (std::numeric_limits<std::streamsize>::max(), '\n');
        } else {
            return number;
        }
    }
}

unsigned int readSize(const char* string) {
    unsigned int size = 0;

    while (true) {
        std::cout << "Enter the " << string << " of the array: ";

        std::cin >> size;

        if (std::cin.fail()) {
            std::cin.clear  ();
            std::cin.ignore (std::numeric_limits<std::streamsize>::max(), '\n');
        } else {
            std::cin.ignore (std::numeric_limits<std::streamsize>::max(), '\n');

            if (size == 0) {
                continue;
            } else {
                return size;
            }
        }
    }
}



int** buildMatrix(unsigned int rows, unsigned int cols) {
    assert(rows     !=  0       );
    assert(cols     !=  0       );

    int** matrix = new (std::nothrow) int*[rows];

    if (matrix != nullptr) {
        for (unsigned int i = 0; i < rows; ++i) {
            matrix[i] = new (std::nothrow) int[cols];

            if (matrix[i] == nullptr) {
                clearMatrix(matrix, i);

                return nullptr;
            }
        }
    }

    return matrix;
}

void clearMatrix(int**& matrix, unsigned int rows) {
    assert(matrix   !=  nullptr );
    assert(rows     !=  0       );

    for (unsigned int i = 0; i < rows; ++i) {
        delete[] matrix[i];
    }

    delete[] matrix;

    matrix = nullptr;
}



void inputMatrix(int** matrix, unsigned int rows, unsigned int cols) {
    assert(matrix   !=  nullptr );
    assert(rows     !=  0       );
    assert(cols     !=  0       );

    std::cout << "Enter the elements of the matrix:\n";

    for (unsigned int i = 0; i < rows; ++i) {
        for (unsigned int j = 0; j < cols; ++j) {
            matrix[i][j] = readNumb();
        }
    }
}

void printMatrix(const int* const* matrix, unsigned int rows, unsigned int cols) {
    assert(matrix   !=  nullptr );
    assert(rows     !=  0       );
    assert(cols     !=  0       );

    std::cout << "The elements of the matrix are:\n";

    for (unsigned int i = 0; i < rows; ++i) {
        for (unsigned int j = 0; j < cols; ++j) {
            std::cout << matrix[i][j] << ' ';
        }

        std::cout << std::endl;
    }
}



void transposeMatrix(const int* const* matrix, unsigned int rows, unsigned int cols) {
    std::cout << "The transposed matrix is: " << std::endl;

    for (unsigned int i = 0; i < cols; ++i) {
        for (unsigned int j = 0; j < rows; ++j) {
            std::cout << matrix[j][i] << ' ';
        }

        std::cout << std::endl;
    }
}
