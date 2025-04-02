# ООП Семинар 07: Още за класовете - влагане и вграждане. Статични членове на клас. 

## Вргаждане и влагане на на класове

### Вграждане на класове

Както използваме `int`, `char` и други типове за полетата на класовете, които създаваме, може да използваме и наши
собствени типове. Това се нарича **вграждане/композиция** на класове. Използва се за създаване на **по-сложни класове чрез по-прости**.

```cpp
#include <iostream>
#include <string>

class Engine {
public:
    Engine(const std::string& type) : type(type) {}

    void start() const {
        std::cout << "Engine (" << type << ") started." << std::endl;
    }

private:
    std::string type;
};

class Car {
public:
    Car(const std::string& model, const Engine& engine) : model(model), engine(engine) {}

    void drive() const {
        std::cout << "Driving " << model << std::endl;
        engine.start();
    }

private:
    std::string model;
    Engine engine;
};

int main() {
    Engine myEngine("V8");
    Car myCar("Mustang", myEngine);

    myCar.drive();

    Engine electricEngine("Electric");
    Car electricCar("Tesla", electricEngine);

    electricCar.drive();

    return 0;
}
```

### Влагане на класове

Допълнително, когато искаме да скрием някакви имплементационни детайли или пък да създадем някакви помощни стуктури,
може да използваме [**влагане**](https://en.cppreference.com/w/cpp/language/nested_types) на класове,
тоест да дефинираме клас вътре в друг клас. Тази техника се използва за **логическо групиране** на класове.

```cpp
#include <iostream>

class Song {
public:
    class Duration { // Nested Duration class
    public:
        Duration(int minutes, int seconds) : minutes(minutes), seconds(seconds) {}

        void printDuration() const {
            std::cout << minutes << " minutes, " << seconds << " seconds";
        }

    private:
        int minutes;
        int seconds;
    };

    Song(const std::string& title, const Duration& duration) : title(title), duration(duration) {}

    void printSongInfo() const {
        std::cout << "Song: " << title << ", Duration: ";
        duration.printDuration();
        std::cout << std::endl;
    }

private:
    std::string title;
    Duration duration;
};

int main() {
    Song::Duration songDuration(3, 45);

    Song mySong("Bohemian Rhapsody", songDuration);

    mySong.printSongInfo();

    Song anotherSong("Stairway to Heaven", Song::Duration(8, 2));

    anotherSong.printSongInfo();

    return 0;
}
```

## Статични член-данни и член-функции

<https://en.cppreference.com/w/cpp/language/static>

### Статични член-данни

- Използваме ги за данни, които са общи за всички обекти от даден клас.
- Инициализираме ги извън класа (в cpp файла, ако правим разделна компилация).
- Достъпваме ги чрез класа, а не чрез обект.
- Паметта се заделя в началото на програмата веднъж и е обща за всички обекти. Унищожава се като програмата приключи.

### Статични член-функции

- Използваме ги за методи, които не зависят от конкретната инстанция на класа. Например някакви
помощни функции.
- Те имат достъп до статичните полета на класа.
- В тях няма указател `this`, защото не са свързани с конкретен обект. Съответно други член-данни не
могат да се ползват, освен статичните.

### Пример

Клас, който следи брой на живи обекти:

```cpp
#include <iostream>

class MyClass {
public:
    static int count;

    MyClass() {
        count++;
    }

    ~MyClass() {
        count--;
    }

    static int getCount() {
        return count;
    }
};

int MyClass::count = 0;

int main() {
    MyClass obj1;
    MyClass obj2;

    std::cout << "Number of MyClass objects: " << MyClass::getCount() << std::endl;

    return 0;
}
```

## Задачи

*Крадени (и леко променени) задачи от практикум на 4-та група от миналата година...*

### Задача 1 :computer:
Създайте клас `Computer`, съдържащ следните полета:
- serial number - генерира се автоматично с последователни числа за всеки нов обект от класа;
- brand (символен низ с произволна дължина);
- processor (символен низ с произволна дължина);
- videocard (символен низ с произволна дължина);
- vram (цяло число);
- hard drive (цяло число);
- weight (цяло число);
- battery life (цяло число);
- price (дробно число);
- quantity (цяло число).

Спазвайте принципа за капсулация на данните. Създайте конструктор, който приема всички полета. 
**Обектите от тип `Computer` трябва да са immutable(не можем да променим обекта след създаването му)**, но
техните полета трябва да бъдат достъпни за четене.
Създайте функции за четене (които не променят обекта!) и писане в текстов и двоичен файл.

Обработете всякакви проблеми с паметта, невалидни данни и т.н. с подходящи изключения.

### Задача 2 :department_store:
Създайте клас `ComputerShop`, описващ компютърен магазин със следните характеристики:
- име (символен низ с произволна дължина);
- списък с компютри (за улеснение, да приемем, че няма да съдържа повече от 100 елемента).

Създайте конструктор, който приема име на магазина.

Създайте следните методи:
- `добавяне на компютър` - ако вече има компютър от съответната марка, увеличава количеството, ако няма, го добавя в списъка. Ако в списъка няма място, да се хвърли изключение.
- `принтиране на списъка с компютри` -- извежда информация към подаден изходен поток.
- `покупка на компютър` - приема brand и пари на купувача. Ако купувачът има достатъчно пари спрямо цената и има достатъчно количество от съответния компютър, осъществява успешна покупка и намалява количеството. В противен случай хвърля подходящо изключение.
- `метод, връщащ всички компютри с наличност, по-голяма от 0` - с опция да филтрира компютри, подходящи за пътуване или такива за игри (за определянето използвайте методите от следващия абзац).

Създайте utility class (клас, съдържащ само статични методи) `ConsultantUtils` с два метода:
- `isGoodForGaming` - приема обект от клас Computer и връща true, ако процесорът е i5 или i7, видео паметта е поне 2 ГБ и хард дискът е поне 512;
- `isGoodForTravel` - приема обект от клас Computer и връща true, ако теглото е не повече от 2.5 кг и животът на батерията е над 6 часа.

Обработете всякакви проблеми с паметта, невалидни данни и т.н. с подходящи изключения.

*Допълнително когато разгледате singleton на лекции:*

Приемете, че във вашия свят има само един единствен магазин за компютри. Подсигурете това, като реализирате design pattern-a `Singleton` за класа `ComputerShop`.

