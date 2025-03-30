#include <iostream>
#include <cassert>
#include <cstring>

/* Спецификатори за достъп
    В C++ всеки член (метод или променлива) на класов тип (struct, class, union) има ниво на достъп.
    Това ниво на достъп определя кой може да достъпва членовете на класа.
    
    В C++ класовете имат три спецификатора за достъп:
        - public -> членовете на класа могат да бъдат достъпвани в рамките на класа, извън класа и в производните класове
        - protected -> ще го разгледаме вбъдеще
        - private -> членовете на класа могат да бъдат достъпвани само в рамките на класа

    В структурите по подразбиране всички членове са public.
*/

struct Simple {
    int value{ 15 }; // public
    bool initialize(const char* name, int age); // public
    void free(); // public

// Казваме, че всичко надолу до следващия спецификатор за достъп е public
public:
    void print();

// Казваме, че всичко надолу до следващия спецификатор за достъп е private
private:
    // Аз харесвам да добавям m_ пред имената на променливите, които са private
    char* m_name{};
    int m_age{};

public:
    void grow();
};

int main() {
    Simple p;
    assert(p.initialize("Ivan", 25));

    std::cout << "Value: " << p.value << std::endl; // Имаме достъп до value, защото е public
    // std::cout << "Name: " << p.name << std::endl; // Нямаме достъп до name, защото е private и ако се пробваме да го достъпим извън класа, ще получим грешка
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
    std::cout << "Name: " << m_name << ", Age: " << m_age << std::endl;
}

void Simple::grow() {
    ++m_age;
}
