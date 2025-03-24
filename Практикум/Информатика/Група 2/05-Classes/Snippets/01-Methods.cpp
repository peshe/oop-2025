#include <iostream>

/* Методи
    Досега когато искахме да извършваме операции с обекти от даден класов тип (struct, class, union),
    използвахме функции, които приемаха обектите като аргументи.
    Това не винаги ще е удобно, а и няма да ни позволи да използваме някои от възможностите на ООП.

    Класовите типове могат да имат собствени функции.
    Тези функции, дефинирани като членове на класовия тип, се наричат методи.
    
    Методите трябва да се декларират в тялото на класа.
    Те могат да се дефинират в тялото на класа или извън него.

    Методи могат да извикват други методи на класовия тип или
    да достъпват членове на класовия топ,дори ако са декларирани след тях.
    Това е възможно, защото компилаторът първо прочита целия клас и след това го компилира.
*/

struct Simple {
    char name[50]{};
    unsigned int age{};
    double weight{};

    // Декларация и дефиниция на метод в тялото на структурата
    void print() {
        std::cout << "Name: " << name << std::endl;
        std::cout << "Age: " << age << std::endl;
        std::cout << "Weight: " << weight << std::endl;
    }

    // Декларация и дефиниция на метод в тялото на структурата
    void grow() {
        ++age;
    }

    // Методите могат да бъдат пренатоварени
    void grow(int years) {
        age += years;
    }

    // Декларация на метод
    void gainWeight(double weight);

    // Декларация на метод
    bool isAdult();

    void hug(const Simple& other) {
        // Методите могат да достъпват методите и членовете на други обекти от същия клас
        std::cout << name << " hugs " << other.name << std::endl;
    }
};

int main() {
    Simple ivan{ "Ivan", 25, 75.5 };

    ivan.print();
    std::cout << "-------" << std::endl;

    ivan.grow();
    ivan.gainWeight(2.5);
    ivan.print();
    std::cout << "-------" << std::endl;

    std::cout << "Is adult: " << std::boolalpha << ivan.isAdult() << std::endl;
    std::cout << "-------" << std::endl;

    Simple maria{ "Maria", 22, 55.5 };

    ivan.hug(maria);

    return 0;
}

// Дефиниция на метод извън тялото на класа
void Simple::gainWeight(double weight) {
    this->weight += weight;
}

// Дефиниция на метод извън тялото на класа
bool Simple::isAdult() {
    return age >= 18;
}
