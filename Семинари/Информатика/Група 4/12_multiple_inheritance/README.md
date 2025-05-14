# ООП Семинар 12: Преговор на наследяване. Множествено наследяване

## Преговор на наследяване. Демонстрация на по-практически пример за полиморфизъм

## Множествено наследяване

C++ позволява наследяването на повече от един базов клас.

При множествено наследяване, конструкторите на базовите класове се извикват в реда, в който са наследени.

### Многозначност/нееднозначност

```cpp
class A {
    void f();
}

class B {
    void f();
}

class C : public A, public B {
    void g();
}

// Ambiguity:
C c;
c.f();

c.A::f();
```

Аналогично е поведението и при виртуални функции -- може да ги припокриваме и през единия, и през другия клас.
При множествено наследяване, виртуалните таблици се обединяват.

### Диамантен проблем. Виртуално наследяване

```cpp
class Person {
    char* name;

public:
    const char* getName() const;
    void setName(const char*);
}

class Student : public Person {
    char* facNum;
    //...
}

class Author : public Person {
    //...
}

class PhDStudent : public Student, public Author {
public:
    const char* getName() const {
        return this->Student::getName();
    }

    void setName(const char* name) {
        this->Student::setName(name);
    }
}
```

В случая имаме две копия на `Person` -- едно в `Student` и едно в `Author`. Това създава различни проблеми:

- От една страна, имаме ненужно използване на ресурси -- имаме заделена динамична памет за името на две места, а не ни трябва;
- От друга, създава се възможност в зависимост от това как гледаме на даден обект, той да има различно име. Трябва да се грижим да
има една и съща информация в двата класа, което не винаги е възможно: Например, дори и в `PhDStudent` да направим метод, който взима/задава
името само през единия клас, то какво ще стане ако извикаме `setName()` във функция `void setPesho(Author& a)` -- нямаме контрол тук и може да се
получи разминаване.

#### Виртуално наследяване

Решаваме горния проблем по следния начин:

```cpp
class Person {
    char* name;

public:
    const char* getName() const;
    void setName(const char*);
}

class Student : virtual public Person {
    char* facNum;
    //...
}

class Author : virtual public Person {
    //...
}

class PhDStudent : public Student, public Author {
    //...
}
```

Виртуалното наследяване не е е без своите проблеми: Когато имаме виртуален базов клас някъде в йерархията, то трябва изрично да го инициализираме:
В случая не разчитаме на `Student` или `Author` да извикат конструктор на `Person`, а трябва в `PhDStudent` да го направим.

```cpp
PhDStudent::PhdStudent(const char* name, ...)
    : Person(name),
    Student(...),
    Author(...)
    {}
```

### Задачи

Какво ще отпечатат следните програми:

#### 1)

```cpp
#include<iostream>
using namespace std;

class A
{
private:
  int x;
public:
  void setX(int i) {x = i;}
  void print() { cout << x; }
};

class B:  public A
{
public:
  B()  { setX(10); }
};

class C:  public A
{
public:
  C()  { setX(20); }
};

class D: public B, public C {
};

int main()
{
    D d;
    d.print();
    return 0;
}
```

#### 2)

```cpp
#include<iostream>
using namespace std;

class A
{
private:
    int x;
public:
  A(int i) { x = i; }
  void print() { cout << x; }
};

class B: virtual public A
{
public:
  B():A(10) {  }
};

class C:  virtual public A
{
public:
  C():A(10) {  }
};

class D: public B, public C {
};

int main()
{
    D d;
    d.print();
    return 0;
}
```
