# ООП семинар 01 -- Преговор от УП. Въведение в C++. Изброен тип

## C++?

- Използва почти същия синтаксис като C за основните неща.
- Въвежда по-високо ниво на абстракция: За разлика от C, C++ не е само процедурен език, а позволява използването и на други програмни парадигми като обектно-ориентираното програмиране, което ще разглеждаме в курса.

## Преговор на C и еквивалент и нови неща в C++

### Вход и изход

```c
#include <stdio.h>

int main() {
    int number;

    printf("Enter an integer: ");

    scanf("%d", &number);

    printf("You entered: %d\n", number);

    return 0;
}
```

```cpp
#include <iostream>

int main() {
    int number;
    std::cout << "Enter a number: ";

    std::cin >> number;

    std::cout << "You entered: " << number << std::endl;

    return 0;
}
```

Основни моменти:

- `cin` сам определя типа на въвежданите данни и не е нужно да се задава формата им;
- При грешен формат на данните, използването на `cin` не води до недефинирано поведение както при `scanf`
- `cout` също е повече type-safe спрямо `printf`, но втория е по-бърз при прост изход;
- `endl` извежда нов ред на екрана по различен начин в зависимост от ОС (но прави и други неща).

### Динамична памет

[Memory Layout of C Programs](https://www.geeksforgeeks.org/memory-layout-of-c-program/)

#### Заделяне на динамична памет в C

```c
#include <stdio.h>
#include <stdlib.h>

int main(void) {
    // Stack variable
    int a = 42;
    int* aPtr = &a;
    printf("%d\n", a);
    printf("%p\n", aPtr);
    printf("%d\n", *aPtr);

    // Heap variable
    int* bPtr = (int*)malloc(sizeof(int));

    // If we haven't checked that the allocation is right we might crash the program
    // with a statement like that:
    // *bPtr = 10;

    // Check if the memory has been allocated
    if (bPtr == NULL) {
        printf("malloc failed\n");
    }

    // Heap array
    int* arrayPtr = (int*)malloc(10 * sizeof(int));

    if (arrayPtr == NULL) {
        printf("malloc failed\n");
    }

    // Don't forget to free the allocated memory!
    free(bPtr);
    free(arrayPtr);

    return 0;
}
```

#### Заделяне на динамична памет в C++

```cpp
#include <iostream>
#include <new>

int main() {
    int a = 42;
    int *aPtr = &a;
    std::cout << a << std::endl;
    std::cout << *aPtr << std::endl;
    std::cout << aPtr << std::endl;

    // Single variable in the heap
    int *bPtr = new(std::nothrow) int(5);
    // Value in the parentheses isn't the size of the variable but rather a value we initialize it with.
    // Same as in C, we must verify that the allocation is successful before using the memory
    if (bPtr != nullptr) {
        *bPtr = 10;
    }

    // Array with 100 elements on the heap
    int *arrayPtr = new(std::nothrow) int[100];
    if (arrayPtr == nullptr) {
        std::cout << "Error allocating memory" << std::endl;
        return 1;
    }

    arrayPtr[0] = 1;
    arrayPtr[1] = 2;
    std::cout << *arrayPtr << std::endl;
    std::cout << arrayPtr[0] << std::endl;
    std::cout << *(arrayPtr + 1) << std::endl;

    // Don't forget to call delete!
    delete bPtr;
    delete[] arrayPtr;

    return 0;
}
```

Основни разлики:

- използваме `new` вместо `malloc()`/`calloc()`;
- не подаваме размера на типа при заделяне на памет;
- `new` може да хвърли изключение, но за момента няма да се интересуваме от това и ще пишем `std::noexcept`
(По-нататък в курса ще разглеждаме exceptions)
- използваме `delete` за единични променливи и `delete[]` за масиви, заделени в динамичната памет, вместо `free()`
- имаме отделен тип `nullptr`, който използваме вместо `NULL` при работа с указатели.

### Псевдоними (references)

#### Какво са псевдонимите?

- Най-просто казано са друго име за дадена променлива;
- Не могат да приемат `nullptr` стойност, тоест винаги сочат към нещо, за разлика от указателите;
- Трябва да се инициализират със стойност при създаването си.

```cpp
#include <iostream>

int main() {
    int original = 10;
    int &ref = original; // ref is a reference to original

    std::cout << original << std::endl;
    std::cout << ref << std::endl;

    ref = 8;

    std::cout << original << std::endl;
    std::cout << ref << std::endl;

    return 0;
}
```

Ще ги използваме най-често при параметрите на функции. Важно е да се различава кога нещо се подава по копие или по име.

```cpp
#include <iostream>

void increment(int a) {
    a++;
}

void incrementPtr(int *a) {
    (*a)++;
}

void incrementRef(int &a) {
    a++;
}

void print(const int &a) {
    // a++; // Will result in a compile error
    std::cout << a << std::endl;
}

int main() {
    int one = 0;
    std::cout << one << std::endl;

    increment(one);
    std::cout << one << std::endl;

    incrementPtr(&one);
    std::cout << one << std::endl;

    incrementRef(one);
    std::cout << one << std::endl;

    return 0;
}
```

#### Припомняне на модификатора const

```cpp
const int* ptrToConstInt1;
int const* ptrToConstInt2;
int* const constPtrToInt = nullptr;
int const* const* constPtrToConstInt;
```

```cpp
const int *const *const magic = nullptr; // How do you read this?
```

### Указатели към функции

Пример:

```cpp
#include <iostream>

typedef int (*OneParamFunction)(int);

void mapTD(int arr[], std::size_t size, OneParamFunction f) {
    for (size_t i = 0; i < size; i++) {
        arr[i] = f(arr[i]);
    }
}

void map(int arr[], std::size_t size, int (*f)(int)) {
    for (size_t i = 0; i < size; i++) {
        arr[i] = f(arr[i]);
    }
}

int addOne(int value) { return value + 1; }

void someOtherFunction(int value) { return; }

int main(int argc, char **argv) {
    int a[] = {1, 2, 3, 4};
    map(a, 4, addOne);
    // map(a, 4, someOtherFunction); // Compile error

    for (size_t i = 0; i < 4; i++) {
        std::cout << a[i] << std::endl;
    }

    return 0;
}
```

## Изброен тип

Съставен тип данни, който обединява множество именувани константи, логически свързани помежду си.

```cpp
enum Colour
{
    BLACK, // BLACK == 0
    GRAY, // GRAY == 1
    WHITE // WHITE == 2
};

enum Colour2
{
    BLACK = 3,
    GRAY, // GRAY == 4
    WHITE = 10
};

void main() {
    Colour colour = GRAY;
    Colour c1 = (Colour) 2;
    Colour c2 = (Colour) 8; // Value not present in the enum

    if (colour == WHITE) {
        std::cout << "White" << std::endl;
    }
}

```

Може да добавим допълнителни „служебни“ стойности за наше улеснение:

```cpp
enum Colour
{
    UNKNOWN = -1,

    WHITE,
    RED,
    YELLOW,
    BLACK,
    GRAY,

    COLOUR_COUNT
};
```

### Enum vs Enum Class

При използването на plain enums, може да възникнат проблеми като:

```cpp
enum Colour {
    black,
    white,
    red
};

int white = 0; // !!!

// Another problem

Colour c = red;
if (c < 14.6) { // Comparing the enum to double?
    //...
}
```

Ако използваме `enum class`, няма да имаме горните проблеми.

```cpp
enum class Color { black, white, red };

Color c = Color::red;
```

[Още информация за изброен тип.](https://en.cppreference.com/w/cpp/language/enum)

## Допълнителни задачи

### Задача 1

Имплементирайте функция от втори ред $g$, която получава (указател към) функция $f$ и естествено число $n$ и връща $f(1) + ... + f(n)$. Използвайте я, за да изчислите:

а) $S = 1 + 2^2 + 3^2 + ... + 10^2$

б) $S = 1 + 2! + ... + 6!$

### Задача 2

Да се напише функция `char* concatAll(const char** stringArray, size_t arraySize)`, която заделя подходящо количество памет за нов низ, записва в него конкатенацията на подадения ѝ масив от низове, и го връща.
За имплементацията да се използват стандартните функции от `cstring`.
