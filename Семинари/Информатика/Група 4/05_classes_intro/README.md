# ООП Семинар 05 -- Класове - идея, видимост. Членове. Декларация и дефиниция.

## Допълнение към миналия път

### Използване на командни аргументи

За задачата от предния път.

```cpp
int main(int argc, char** argv)
{
    std::cout << "The number of command arguments is: " << argc << std::endl;
    for (int i = 0; i < argc; ++i)
    {
        std::cout << "Argument #" << i + 1 << ": " << argv[i] << std::endl;
    }

    std::cout << std::endl;

    return 0;
}
```

### Буфери при потоците

Миналия път имаше въпрос за 110 ред от [тук](../../Група 1/files/files2.cpp). Най-просто казано, `file.seekg(file.tellg());` се прави, за да се
синхронизират буферите за четене и писане, тъй като не е сигурно винаги точно какво има в тях при едновременно четене и писане от/във файл.

Още информация: <https://stackoverflow.com/questions/8116541/what-exactly-is-streambuf-how-do-i-use-it>

## Основни принципи в ООП

- **Абстракция** - процесът на скриване на ненужни подробности;
- **Капсулация** - един обект трябва да предоставя на ползващия го само пряко необходимите му средства за управление;
- **Наследяване**
  - позволява да бъдат дефинирани и създавани обекти, които са специализирани варианти на вече съществуващи обекти;
  - класът наследник взема всички свойства и методи на класа-родител;
- **Полиморфизъм** - представлява свойството на обектите от един и същи тип да имат един и същи интерфейс, но с различна реализация на този интерфейс.

## Класове в C++

### Структурите до момента и проблемите с тях. Преход към класове

Пример за (частична) реализация на динамичен маси (масив, който ще променя размера си; в курса по СДП по-подробно):

```cpp
#include <cassert>
#include <iostream>

struct DynamicArray {
    int *data;
    std::size_t size;
    std::size_t allocated;
};

void initialize(DynamicArray &da) {
    da.size = 0;
    da.allocated = 0;
    da.data = nullptr;
}

void allocate(DynamicArray &da, std::size_t size) {
    da.allocated = size;
    da.data = new(std::nothrow) int[da.allocated];
}

int &at(DynamicArray &da, std::size_t index) {
    assert(index < da.size);
    return da.data[index];
}

void deallocate(DynamicArray &da) {
    delete[] da.data;
    da.allocated = 0;
    da.size = 0;
    da.data = nullptr;
}

```

Нека да разгледаме някакво примерно използване на този динамичен масив:

```cpp
void f() {
    DynamicArray da;
    initialize(da);
    allocate(da, 10);
    at(da, 0) = 1;
    at(da, 1) = 2;
    deallocate(da);
}

int main(int argc, const char *argv[]) {
    while (true) {
        f();
    }
    return 0;
}
```

Възникват някои проблеми:

- Може да забравим да извикаме `deallocate()` и да тече памет;
- Може да забравим да инициализираме и да работим с невалидни такива;
- Някой „отвън“ може да промени състоянието на динамичния масив;
- Трябва всеки път да пишем за кой масив се отнася съответната функция;
- и така нататък...

#### Клас и обект. Указател `this`

Ще решим проблема с писането на това за коя инстанция се отнася по следния начин:

```cpp
struct DynamicArray {
    int *data;
    std::size_t size;
    std::size_t allocated;

    void initialize() {
        this->size = 0;
        this->allocated = 0;
        this->data = nullptr;
    }

    void allocate(std::size_t size) {
        this->allocated = size;
        this->data = new(std::nothrow) int[this->allocated];
    }

    int &at(std::size_t index) {
        assert(index < this->size);
        return this->data[index];
    }

    void deallocate() {
        delete[] this->data;
        this->allocated = 0;
        this->size = 0;
        this->data = nullptr;
    }
};

void f() {
    DynamicArray da;
    da.initialize();
    da.allocate(10);
    da.at(0) = 1;
    da.at(1) = 2;
    da.deallocate();

    DynamicArray da2;
    da2.initialize();
    da.allocate(100);
    da2.at(0) = 3;
    da2.at(1) = 4;
    da2.at(2) = 5;
    da2.deallocate();
}
```

- **Клас** -- нещо общо, някакъв тип, например куче, кола, човек, динамичен масив;
- **Обект** -- конкретен представител (инстанция) на даден клас (тип) -- Шаро, Пешо, da1;

Променливите в даден клас се наричат **член-данни** или полета. Функциите -- **член-функции** или методи.

Указателят `this` сочи към конкретния обект, с който работим.

Забележка: Не всеки обект си има собствено копие на функциите. Те живеят на едно място, разликите при извикването им върху различни обекти идва
от указателя `this`.

### Енкапсулация. Модификатори за достъп (Access Modifiers)

Другият от проблемите, който имаме е с достъпът: Данните на динамичния масив лесно могат да бъдат променяни от „външния свят“.

| Модификатор | Действие                                            |
| ----------- | --------------------------------------------------- |
| public      | Достъп отвсякъде в програмата (т.е. „външния свят“) |
| protected   | Достъп само вътре в класа и за наследниците\*       |
| private     | Достъп само вътре в класа                           |

*\*За наследници ще говорим по-нататък в отделна тема за наследяване в ООП*

#### Разлика между `class` и `struct` в C++

Основната разлика между `class` и `struct` в C++ е достъпът по подразбиране. В структурата е публичен, в класовете -- обратно, частен.

При C, думата клас изобщо не съществува и структурите там не могат да съдържат методи както в C++.

Въпреки че са почти едни и същи, използваме `struct` за по-прости сценарии, в които имаме състевен тип, без да включваме ООП принципи.
Когато имаме член-данни и член-функции, енкапсулация и така нататък -- използваме `class`.

#### Правило за най-малките привилегии. Принцип за енкапсулация

Добър принцип за работа е да се следва т.нар. правило за най-малките привилегии: Тоест даден човек/код от програмата да има **достъп само до
нещата, които са му нужни** и нищо повече. В нашия контекст, по подразбиране пишем всичко енкапсулирано и само ако има нужда правим достъпа `public` или `protected`.

Това е основен принцип за сигурност не само в код, но и в организации. Разбира се, ние се интересуваме от първата част -- по този начин компилаторът
ще ни предпазва да правим грешки в логиката на програмата, защото достъпваме нещо, което не трябва.

Принципът за енкапсулация е именно това -- да се скриват данни и методи от външния свят с цел контрол на достъпа.

```cpp
class DynamicArray {
    // Private by default, these fields cannot be messed up from the outside
    int *data;
    std::size_t size;
    std::size_t allocated;

public:
    void initialize() {
        this->size = 0;
        this->allocated = 0;
        this->data = nullptr;
    }

    void allocate(std::size_t size) {
        this->allocated = size;
        this->data = new(std::nothrow) int[this->allocated];
    }

    int &at(std::size_t index) {
        assert(index < this->size);
        return this->data[index];
    }

    void deallocate() {
        delete[] this->data;
        this->allocated = 0;
        this->size = 0;
        this->data = nullptr;
    }
};
```

#### Getter/Setter (Selector/Mutator) методи

Често се налага все пак външния свят да знае за данните вътре в класа. За да дадем някакъв достъп, без да нарушаваме
енкапсулацията, използваме т.нар. getter и setter методи.

```cpp
std::size_t getSize() const {
    return this->size;
}
```

*\*За думичката const по-горе ще говорим в следващи часове.*

Общ вид за setter:

```cpp
void set<member_name>(<member_type> value)
{
    if (<validate the given value>) {
    <member_name> = value;
    }
}
```

### Декларация и дефиниция на клас

В голяма част от случаите ще пишем декларацията на класа в отделен header файл, а дефинициите на методите в друг source файл.

```cpp
// DynamicArray.hpp

class DynamicArray {
    int *data;
    std::size_t size;
    std::size_t allocated;

public:
    void initialize();

    void allocate(std::size_t size);

    int &at(std::size_t index);

    void deallocate();
};
```

```cpp
// DynamicArray.cpp

#include "DynamicArray.hpp"

// We don't have a global function initialize but we have one in DynamicArray
// so we use the :: operator

void DynamicArray::initialize() {
    this->size = 0;
    this->allocated = 0;
    this->data = nullptr;
}

void DynamicArray::allocate(std::size_t size) {
    this->allocated = size;
    this->data = new(std::nothrow) int[this->allocated];
}

int & DynamicArray::at(std::size_t index) {
    assert(index < this->size);
    return this->data[index];
}

void DynamicArray::deallocate() {
    delete[] this->data;
    this->allocated = 0;
    this->size = 0;
    this->data = nullptr;
}
};
```

### Конструктори

Конструкторът е специална член-функция на класа, която се извиква автоматично при създаването
на обект от този клас. Конструкторът се извиква един-единствен път при създаването на обекта.

Конструкторите се използват, за да инициализират всички член-данни на обекта с подходящи,
валидни стойности, подадени от потребителя. Общо казано, конструкторите подготвят обекта за
работа. Това може да означава и да се задели динамична памет, да се отвори файл, да се направи
връзка с база от данни и др.

```cpp
DynamicArray::DynamicArray() {
    this->size = 0;
    this->allocated = 0;
    this->data = nullptr;
}
```

С параметри:

```cpp
DynamicArray::DynamicArray(std::size_t allocated) {
    this->size = 0;
    this->allocated = allocated; // This doesn't make much sense but it's just an example
    this->data = nullptr;
}
```

Още за конструктори и жизнения цикъл на обектите -- в следващите часове...

## Задачи

### Задача 1

Реализирайте клас `Interval`, който представлява интервал  [a, b] (задължително $а \leq b$)  от реалната права.
Нашият интервал ще бъде дискретен - началото и краят му ще бъдат цели числа и ще разглеждаме само точки, които са цели числа. Релизирайте следният интерфейс:

 - Подразбиращ се контруктор, който създава интервала **[0, 0]**.
 - Конструктор, който приема двата параметъра. Ако $а \leq b$, то създава интервала **[a, b]**. В противен случай, създава **[0, 0]**.
 - Член-функция, която връща **дължината на интервала**.
 - Член-функция, която приема число и проверява **дали е част от интервала**.
 - Член-функция, която връща **броя на простите числа** в интервала.
 - Член-функция, която връща **броя на числата в интервала**, които са палиндорми.
 - Член-функция, която връща **броя на числата, които нямат повтарящи цифри**.
 - Член-функция, която връща дали началото и края на интервала са **степени на 2-ката**. (Например за [2, 16] - истина)
 - Член-функция, която приема интервал и връща **сечението на текущия интервал с подадения**.  (Сечението на [1, 5]  [3, 7]  e [3, 5]).
 - Член-функция, която приема интервал и връща дали подадения (като параметър) интервал е **подинтервал на текущия** (обектът, от който се извиква функцията).

  **Пример за работа с класа:**
 ```c++

int main()
{
     Interval t1(3,10); // [3, 10]
     Interval t2(4,14); // [4, 14]
     Interval t3; // [0, 0]

     Interval result = t1.intersect(t2); // [4, 10]

     t2.isSuperInterval(result); //true

     result.calcPrimeNumbersInTheInterval() // 2 (only 5 and 7)
}
 ```
