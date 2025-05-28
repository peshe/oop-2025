# ООП Семинар 14: Още за шаблоните. SOLID принципи

## Разделна компилация

От предния път знаем, че за да може компилаторът да генерира код по даден шаблон, той трябва да „вижда“
както декларациите, така и пълните дефиниции на шаблона в един translation unit.

Ако разделим шаблонен клас на `hpp/cpp` файлове, няма да сработи.

### Традиционен подход

Пишем всичко в header файла. Това е най-лесният начин, по който може да се справим с проблема по-горе.

### Explicit instantiation

```cpp
#ifndef MY_TEMPLATE_H
#define MY_TEMPLATE_H

template <typename T>
class MyClass {
public:
    MyClass(T value);
    void printValue() const;
};

#endif // MY_TEMPLATE_H
```

```cpp
#include "my_template.h"
#include <iostream>

template <typename T>
MyClass<T>::MyClass(T value) : m_value(value) {
    // Definition
}

template <typename T>
void MyClass<T>::printValue() const {
    std::cout << "Value: " << m_value << std::endl;
}

// Explicit instantiations for the types you expect to use
template class MyClass<int>;
template class MyClass<double>;
```

По този начин ще направим хедър файла по-чист и интерфейсът ще е по-ясен, но трябва предварително
да знаем всички типове, с които ще се използва темплейта, което не винаги е приолжимо.
Ако някой ползва шаблона за друг тип, който не е описан, ще получи грешка от linker-а.

### .inl файл

Има няколко файлови разширения, които не са задължителни в C++ стандарта, които позволяват по-добро разделение на кода.

Това са:

- `.inl` (inline), което често се ползва за дефиниция на шаблони на член-функции или за функции, които са `inline` по принцип.
Целта е кодът да се раздели, като този файл се включва в основния `.h/.hpp` файл;
- `.incl` -- include, което е пдобно на горното
- `.inc` -- като горното

#### Пример за използване

```cpp
#ifndef MY_TEMPLATE_H
#define MY_TEMPLATE_H

#include <iostream>

template <typename T>
class MyClass {
public:
    MyClass(T value);
    void printValue() const;

private:
    T m_value;
};

// Include the implementation file directly into the header
#include "my_template.inl"

#endif // MY_TEMPLATE_H
```

```cpp
// my_template.inl

template <typename T>
MyClass<T>::MyClass(T value) : m_value(value) {
    // Definition
}

template <typename T>
void MyClass<T>::printValue() const {
    std::cout << "Value: " << m_value << std::endl;
}
```

#### Какво е inline функция

Накратко казано, това е препоръка към компилатора, че може да спести извикването на дадена функция по стандартния начин,
като вгради кода на функцията на мястото, където е извикана.

Допълнително, `inline` оказва влияние и на [ODR (One Definition Rule)](https://en.cppreference.com/w/cpp/language/definition.html).

## Шаблони при наследяване и приятели

```cpp
template<class T>
class Base
{
//...
};

template<class T1>
class Derived : public Base<T1>
{
//...
    friend class Other<T1>;
};
```

Когато наследяваме шаблонен клас, трябва и наследникът да е шаблонен, за да „извика“ базовия със съответния шаблонен тип.
Алтернативно, наследникът може да използва базов клас с конкретен тип, например `Base<int>`. Друга възможност е да се
изпусне типът когато имаме дефолтен такъв в шаблонния хедър на базовия клас, тоест:

```cpp
template<class T = int>
class Base
{
//...
};

class Derived : public Base<>
{
//...
};
```

Аналогично е и при приятелски класове/функции.

## Нетипови шаблонни параметри

```cpp
template<typename T, std::size_t Capacity>
class Array {
public:
    Array(): current_size(0) { }

    T &operator[](std::size_t index) {
        if (index >= Capacity) {
            throw std::out_of_range("Array index out of range");
        }
        return data[index];
    }

    const T &operator[](std::size_t index) const;

    std::size_t size() const {
        return Capacity;
    }

private:
    T data[Capacity];
    size_t current_size;
};

int main() {
    Array<int, 10> intArray;

    Array<double, 50> doubleArray;

    std::cout << intArray.size() << std::endl;
    std::cout << doubleArray.size() << std::endl;

    intArray[0] = 5;
    doubleArray[49] = 123.45;

    std::cout << intArray[0] << std::endl;
    std::cout << doubleArray[49] << std::endl;

    return 0;
}
```

Още един пример:

```cpp
template<unsigned X>
unsigned fact() {
    return X * fact<X - 1>();
}

template<>
unsigned fact<0>() {
    return 1;
}

int main() {
    std::cout << fact<6>() << std::endl; // Works as expected

    unsigned n;
    std::cin >> n;
    std::cout << fact<n>() << std::endl; // Compile error!
}
```

В случая имаме исканото поведение, но на цената на повече генерирани функции и невъзможност функцията да се извиква
с произволен параметър, който не е известен по време на компилация. Такива функции се ползват, когато предварително трябва
да се генерират и попълнят известни стойности.

---

*Още за шаблонните параметри: <https://en.cppreference.com/w/cpp/language/template_parameters>*

## Допълнителни неща (извън материала) за шаблони

- <https://en.cppreference.com/w/cpp/header/type_traits>
- <https://en.cppreference.com/w/cpp/language/pack>

Пример за използването им за добавяне на функционалност към класа `Vector` от предното упражнение:

```cpp
template <typename T>
template <typename... Args>
std::enable_if_t<std::is_constructible<T, Args...>::value, void>
Vector<T>::EmplaceBack(Args&&... args){
    PushBack(T(std::forward<Args>(args)...));
}
```

## SOLID принципи

### Single Responsibility Principle (SRP)

Един клас трябва да има само и единствено **една** причина да се променя. Тоест, един клас трябва да отговаря само за едно нещо.
Вече сме виждали това поведение когато сме писали функции -- една функция прави конкретно нещо, а не незнайсет едновременно.

#### Лош пример

```cpp
class User {
public:
    void createUser(const std::string& username, const std::string& password) {
        // Logic to create user in the database
        // Logic to send a welcome email
    }
    // ... other user-related methods
};
```

В случая ако има промяна в начина, по който се съхраняват потребители в базата данни, то класът трябва да се промени.
Ако пък има промяна в начина за пращане на мейли, също.

#### Добър пример

```cpp
class UserRepository {
public:
    void saveUser(const std::string& username, const std::string& password) {
        // Logic to save user to the database
    }
};

class EmailService {
public:
    void sendWelcomeEmail(const std::string& emailAddress) {
        // Logic to send a welcome email
    }
};

class UserCreator {
private:
    UserRepository& userRepository;
    EmailService& emailService;
public:
    UserCreator(UserRepository& repo, EmailService& service)
        : userRepository(repo), emailService(service) {}

    void createUser(const std::string& username, const std::string& password, const std::string& email) {
        userRepository.saveUser(username, password);
        emailService.sendWelcomeEmail(email);
    }
};
```

Разделяме логиката за съхранение на потребители от тази за изпращането на мейли.

### Open-Closed Principle (OCP)

Класовете или модулите трябва да бъдат отворени за надграждане, но затворени за промени.
Вече сме виждали това нещо под формата на полиморфизмът, който ползваме:

#### Лош пример

```cpp
class Shape {
public:
    enum Type { Circle, Square };
    Type type;
    double radius;
    double side;

    Shape(Type t) : type(t) {}
    Shape(double r) : type(Circle), radius(r) {}
    Shape(double s, bool isSquare) : type(Square), side(s) {}

    double calculateArea() {
        if (type == Circle) {
            return 3.14159 * radius * radius;
        } else if (type == Square) {
            return side * side;
        }
        return 0.0;
    }
};
```

Ако искаме да добавим нова фигура, трябва да променим класа, както и метода вътре.

#### Добър пример

```cpp
class Shape {
public:
    virtual double calculateArea() const = 0;
    virtual ~Shape() = default;
};

class Circle : public Shape {
private:
    double radius;
public:
    Circle(double r) : radius(r) {}
    double calculateArea() const override {
        return 3.14159 * radius * radius;
    }
};

class Square : public Shape {
private:
    double side;
public:
    Square(double s) : side(s) {}
    double calculateArea() const override {
        return side * side;
    }
};

class Triangle : public Shape {
private:
    double base;
    double height;
public:
    Triangle(double b, double h) : base(b), height(h) {}
    double calculateArea() const override {
        return 0.5 * base * height;
    }
};

```

Ако искаме да добавим нова фигура, трябва да създадем нов клас, без да променяме нищо съществуващо.

### Liskov Substitution Principle (LSP)

    If S is a subtype of T, then objects of type T in a program may be replaced with objects of type S
    without altering any of the desirable properties of that program (e.g. correctness)

Този принцип изисква подкласовете не само да задоволяват синтактичните очаквания, но и поведенческите такива на своите родители.
Kато потребител на клас би трябвало да може да използваме всяко от неговите деца, които могат да ни бъдат предадени,
без да се интересувамe кое конкретно дете се използва.
Това означава, че трябва да гарантираме, че аргументите, както и всички върнати стойности на децата са последователни.

#### Лош пример

```cpp
class Bird {
public:
    virtual void fly() {
        std::cout << "Bird is flying." << std::endl;
    }
};

class Penguin : public Bird {
public:
    void fly() override {
        // Penguins cannot fly, this breaks the expectation of the base class's fly() method
        // This might throw an exception, do nothing, or print an error,
        // which would surprise client code expecting a flying bird.
        std::cout << "Penguins cannot fly." << std::endl;
    }
};

// Client code:
// Bird* bird = new Penguin();
// bird->fly(); // This will print "Penguins cannot fly." which is unexpected
//               // if you just expect any Bird to fly.
```

#### Добър пример

```cpp
class Bird {
public:
    virtual void eat() {
        std::cout << "Bird is eating." << std::endl;
    }
    virtual ~Bird() = default;
};

class FlyingBird : public Bird {
public:
    virtual void fly() {
        std::cout << "Flying bird is flying." << std::endl;
    }
};

class Penguin : public Bird { // Penguin inherits from Bird, not FlyingBird
public:
    void slide() {
        std::cout << "Penguin is sliding on ice." << std::endl;
    }
};

class Eagle : public FlyingBird {
public:
    void fly() override {
        std::cout << "Eagle is soaring high!" << std::endl;
    }
};

```

Разделяме общите неща за всички птици от тези, които са присъщи за летящите птици. Това разделяне ни осигурява
предвидимо поведение.

### Interface Segregation Principle (ISP)

Клиентите не трябва да зависят от интерфейси, които не използват. Тоест е по-добре да се създадат множество на брой по-малки
интерфейси, от колкото един голям.

#### Лош пример

```cpp
class Machine {
public:
    virtual void print() = 0;
    virtual void scan() = 0;
    virtual void fax() = 0;
};

class SimplePrinter : public Machine {
public:
    void print() override { /* ... */ }
    void scan() override { /* Not applicable */ } // Forced to implement
    void fax() override { /* Not applicable */ }  // Forced to implement
};
```

Не всички интерфейски за мултифункционално устройство принтер-скенер-факс са приложими за обикновен принтер, който няма скенер.
Чисто физически няма смисъл принтерът да има копче „сканиране“, без да има скенер. (например)

#### Добър пример

```cpp
class IPrinter {
public:
    virtual void print() = 0;
    virtual ~IPrinter() = default;
};

class IScanner {
public:
    virtual void scan() = 0;
    virtual ~IScanner() = default;
};

class IFax {
public:
    virtual void fax() = 0;
    virtual ~IFax() = default;
};

class MultiFunctionPrinter : public IPrinter, public IScanner, public IFax {
public:
    void print() override { /* ... */ }
    void scan() override { /* ... */ }
    void fax() override { /* ... */ }
};

class SimplePrinter : public IPrinter {
public:
    void print() override { /* ... */ }
};
```

### Dependency Inversion Principle (DIP)

    High-level modules should not depend on low-level modules. Both should depend on abstractions (e.g. interfaces).
    Abstractions should not depend on details. Details (concrete implementations) should depend on abstractions.

Тоест, нашите класове трябва да зависят от интерфейси или абстрактни класове, вместо от конкретни класове и функции.

#### Лош пример

```cpp
class LightBulb {
public:
    void turnOn() { std::cout << "LightBulb is on." << std::endl; }
    void turnOff() { std::cout << "LightBulb is off." << std::endl; }
};

class Switch {
private:
    LightBulb bulb; // Direct dependency on a concrete LightBulb
public:
    void press() {
        bulb.turnOn();
    }
};
```

#### Добър пример

```cpp
class ISwitchableDevice {
public:
    virtual void turnOn() = 0;
    virtual void turnOff() = 0;
    virtual ~ISwitchableDevice() = default;
};

class LightBulb : public ISwitchableDevice {
public:
    void turnOn() override { std::cout << "LightBulb is on." << std::endl; }
    void turnOff() override { std::cout << "LightBulb is off." << std::endl; }
};

class Fan : public ISwitchableDevice {
public:
    void turnOn() override { std::cout << "Fan is spinning." << std::endl; }
    void turnOff() override { std::cout << "Fan is stopped." << std::endl; }
};

class Switch {
private:
    ISwitchableDevice& device;
public:
    Switch(ISwitchableDevice& d) : device(d) {}

    void press() {
        device.turnOn();
    }
};

```

```cpp
LightBulb bulb;
Switch lightSwitch(bulb);
lightSwitch.press();

Fan fan;
Switch fanSwitch(fan);
fanSwitch.press();
```

В случая сме направили абстракцията за някакъв уред, който може да се включва и изключва. Лампата и вентилаторът са
такива. Електрическото копче не се интересува дали включва или изключва лампа, вентилатор или нещо друго. Логиката му се
основава само на абстракцията за нещо, което се включва и изключва.

