#include <iostream>
#include <cassert>
#include <cstring>

/* Класове
    В C++ разликата между клас и структура е само в това,
    че в класа членовете по подразбиране са private,а в структурата са public.

    Всичко, което може да се направи със структура, може да се направи и с клас.
    Всичко, което може да се направи с клас, може да се направи и със структура.
    
    Генерално е прието да се използва клас, когато имаме методи и данни, а структура, когато имаме само данни.
    Попринцип е прието, ако използваме структури да се избягва използването на спецификатори за достъп.
*/

class Simple {
    int value{ 15 }; // private

public:
    bool initialize(const char* name, int age);
    void free();

    void print();

    void grow();

private:
    char* m_name{};
    int m_age{};
};

int main() {
    Simple p;
    assert(p.initialize("Ivan", 25));

    // std::cout << "Value: " << p.value << std::endl; // Имаме достъп до value, защото е private
    std::cout << "-----------------" << std::endl;

    p.print();
    std::cout << "-----------------" << std::endl;

    p.grow();
    p.print();

    p.free();

    return 0;
}

bool Simple::initialize(const char* name, int age) {
    m_name = new (std::nothrow) char[strlen(name) + 1];

    if (m_name == nullptr) {
        return false;
    }

    strcpy(m_name, name);
    m_age = age;

    return true;
}

void Simple::free() {
    delete[] m_name;
    m_name = nullptr;
}

void Simple::print() {
    std::cout << "Name: " << m_name << std::endl;
    std::cout << "Age: " << m_age << std::endl;
}

void Simple::grow() {
    m_age++;
}
