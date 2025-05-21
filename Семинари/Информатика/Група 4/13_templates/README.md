# ООП Семинар 13: Шаблони на функции и класове

## Шаблони на функции

### Какъв проблем решават?

Вместо да пишем един и същи повтарящ се код за множество типове:

```cpp
void swap(int& a, int& b) {
    int temp = a;
    a = b;
    b = temp;
}

void swap(double& a, double& b) {
    double temp = a;
    a = b;
    b = temp;
}
```

Можем да напишем **шаблон на функция**:

```cpp
template<typename Type>
void swap(Type& a, Type& b) {
    Type temp = a;
    a = b;
    b = temp;
}
```

Когато извикаме съответната функция с някакви типове, компилаторът **генерира** код за съответния тип:

```cpp
int main() {
    int x = 5, y = 10;
    double d1 = 3.14, d2 = 2.71;
    char c1 = 'A', c2 = 'B';

    std::cout << "Преди размяната (int): x = " << x << ", y = " << y << std::endl;
    swap(x, y); // Компилаторът генерира swap<int>(x, y)
    std::cout << "След размяната (int): x = " << x << ", y = " << y << std::endl;

    std::cout << "Преди размяната (double): d1 = " << d1 << ", d2 = " << d2 << std::endl;
    swap(d1, d2); // Компилаторът генерира swap<double>(d1, d2)
    std::cout << "След размяната (double): d1 = " << d1 << ", d2 = " << d2 << std::endl;

    std::cout << "Преди размяната (char): c1 = " << c1 << ", c2 = " << c2 << std::endl;
    swap(c1, c2); // Компилаторът генерира swap<char>(c1, c2)
    std::cout << "След размяната (char): c1 = " << c1 << ", c2 = " << c2 << std::endl;

    return 0;
}
```

#### Явно указване на типа

Понякога компилаторът не може да реши сам какво трябва да генерира:

```cpp
#include <iostream>

template<typename T>
const T& min(const T &a, const T &b) {
    return a < b ? a : b;
}

int main() {
    int x = 5;
    double y = 3.14;

    std::cout << min(x, y) << std::endl; // Dosn't work!
    std::cout << min(x, (int)y) << std::endl;
    std::cout << min((double)x, y) << std::endl;
    std::cout << min<int>(x, y) << std::endl;

    return 0;
}
```

### Overloading

Компилаторът вижда, че има функция за int и не използва шаблона:

```cpp
template<typename Type>
const Type& f(const Type& a, const Type& b) {
    // ...
}

int f(int a, int b) {
    // ...
}

int main() {
    int x = 2, y = 5;

    f(y, x); // Тук се извиква int функцията
    f<int>(x, y); // Тук се използва шаблона, за да се генерира функция

    return 0;
}
```

### Специализация на шаблони

Можем да зададем специфично поведение когато шаблонът се извиква с даден тип:

```cpp
template<typename T>
const T &min(const T &a, const T &b) {
    return a < b ? a : b;
}

template<>
const int &min(const int &a, const int &b) {
    std::cout << "Int spec: " << a << " " << b << std::endl;
    return a < b ? a : b;
}
```

### `typename` vs `class`

За нашите цели са изцяло заменими когато пишем шаблони. Повече информация може да потърсите в интернет: <https://stackoverflow.com/questions/2023977/what-is-the-difference-between-typename-and-class-template-parameters#2024173>

## Шаблони на класове

### Основен синтаксис

```cpp
template <typename T>

class ClassName {
public:
    ClassName(T initialValue);
    T getValue() const;
    void setValue(T newValue);

private:
    T memberVariable;
};
```

### Изисквания към типовете

Трябва да внимаваме какво изискваме неявно към типовете, за които ще се използва шаблонът -- дали да имат конструктор по подразбиране,
дали трябва да имат копиращ конструктор, оператор за присвояване, оператор за сравнение и т.н.

В случая примерът не работи за `MyInt`, защото изискваме типът да има конструктор, който може да използва `int`:

```cpp
template<typename T>
class Box {
public:
    Box(const T &val1 = 0, const T &val2 = 0): x(val1), y(val2) {
    }

private:
    T x;
    T y;
};

class MyInt {
    MyInt(const MyInt &other) = delete;

    int value;
};

int main() {
    Box<int> box1;
    Box<double> box2;
    Box<MyInt> box3;

    return 0;
}
```

Дори и да променим примера, като се използват дефолтни конструктори:

```cpp
    Box(const T &val1 = T(), const T &val2 = T()): x(val1), y(val2) {}
```

Пак имаме проблем, защото `MyInt` няма копиращ конструктор.

### Специализация на шаблон на клас

Както при функциите, така и при шаблоните на класове, може да задаваме различно поведение при съответен тип:

```cpp
#include <iostream>

template<typename T>
class Box {
public:
    Box(T val) : content(val) {
    }

    T getContent() const { return content; }
    void printType() const { std::cout << "Общ шаблон на Box" << std::endl; }

private:
    T content;
};

template<>
class Box<bool> {
public:
    Box(bool val) : flag(val) {
    }

    bool getContent() const { return flag; }
    void flip() { flag = !flag; } // Специален метод за bool
    void printType() const { std::cout << "Специализация на Box за bool" << std::endl; }

private:
    bool flag;
};

int main() {
    Box<int> intBox(10);
    intBox.printType(); // Извежда "Общ шаблон на Box"
    std::cout << "IntBox: " << intBox.getContent() << std::endl;

    Box<bool> boolBox(true);
    boolBox.printType(); // Извежда "Специализация на Box за bool"
    std::cout << "BoolBox: " << boolBox.getContent() << std::endl;
    boolBox.flip();
    std::cout << "BoolBox след flip: " << boolBox.getContent() << std::endl;

    return 0;
}
```

## Задача

Напишете шаблон на клас `Vector`, който представя динамичен масив, наподобяващ този от стандартнта библиотека [`std::vector`](https://en.cppreference.com/w/cpp/container/vector).
