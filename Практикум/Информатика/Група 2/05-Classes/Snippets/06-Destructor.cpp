#include <iostream>
#include <cstring>
#include <cassert>

/* Деструктори
    *   Деструкторите са специални методи (подобно на конструкторите),
        които се извикват автоматично,когато обектът излиза от обхвата на действие.
    
    *   Те се използват за освобождаване на ресурси, които са били заделени по време на живота на обекта.

    *   Деструкторите нямат тип на връщане и не приемат аргументи.
        Името на деструктора е името на класа, пред което се добавя ~.

    *   Един клас може да има само 1 деструктор.

    *   Деструкторите се извикват в обратен ред на конструкторите.
        Това означава, че ако имаме вложени обекти, първо ще се извика деструктора на най-вътрешния обект,
        след това на по-външния и така нататък.

    *   Деструкторите може да бъдат извикани експлицитно, но това не е препоръчително и трябва максимално да се избягва.
        Това може да доведе до непредвидими проблеми и грешки в програмата.

    *   Компилаторът автоматично генерира деструктор, ако ние не сме го дефинирали, но той ще е празен.
*/

class Person {
public:
    Person();
    Person(const char* name, int age);

    ~Person();

    void setName(const char* name);

    void print();

private:
    char* m_name{ nullptr };
    int m_age{ 0 };
};

class Simple {
public:
    Simple() {
        std::cout << "Simple::Simple() called" << std::endl;
    }

    ~Simple() {
        std::cout << "Simple::~Simple() called" << std::endl;
    }
};

class Nested {
public:
    Nested() {
        std::cout << "Nested::Nested() called" << std::endl;
    }

    ~Nested() {
        std::cout << "Nested::~Nested() called" << std::endl;
    }

private:
    Simple m_simple{};
};

int main() {
    Person person1;
    person1.print();

    {
        Person person2("John", 25);
        person2.print();
    }

    std::cout << "--------------------------------" << std::endl;

    Nested nested{};

    return 0;
}

Person::Person() : m_age(0) {
    std::cout << "Person::Person() called" << std::endl;

    this->setName("Unknown");
    assert(this->m_name != nullptr);
}

Person::Person(const char* name, int age) : m_age(age) {
    std::cout << "Person::Person(const char*, int) called" << std::endl;

    assert(age >= 0 && age <= 150);

    this->setName(name);
    assert(name != nullptr);
}

Person::~Person() {
    std::cout << "Person::~Person() called" << std::endl;

    delete[] this->m_name;
    this->m_name = nullptr;
}

void Person::setName(const char* name) {
    delete[] this->m_name;

    this->m_name = new (std::nothrow) char[strlen(name) + 1];
    
    if (!this->m_name) {
        std::cout << "Memory allocation error!" << std::endl;
        this->m_name = nullptr;

        return;
    }
    
    strcpy(this->m_name, name);
}

void Person::print() {
    if (this->m_name == nullptr) {
        std::cout << "Cannot print person information, because memory allocation failed earlier!" << std::endl;

        return;
    }

    std::cout << "Name: " << this->m_name << ", Age: " << this->m_age << std::endl;
}
