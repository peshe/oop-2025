# Наследяване

## Хора които не правят примерния проект (Система за менежиране на работници)
### Лесни задачки
**Задача 1**

Направете базов клас `Person`, с следните член данни и член функции:
- Функцията `void start()`
- Уникален идентификационен номер
- Име (Името по подразбиране е `Georgi`)

Пример:
```c++
Person* p1 = new Person("John");
p1->start(); // Output: "Starting John, ID: 1"
```

**Задача 2**

Напишете два класа `Sales` и `Engineer`, двата класа трябва да наследяват `Person`, като трябва да имат следния изход:

Пример:
```c++
Sales pt;
pt.start(); // Output: "Georgi starting to sell, ID: 1"

Engineer ct;
ct.start(); // Output: "Georgi starting to code, ID: 2"
```
**Задача 3**
Имплементирайте конструктор, деструктор, копи конструктор и move семантики за всички класове.

Пример
```c++
Sales a;
Sales b = a;
std::cout << a.getId() << " " << b.getId(); // Output: "1 1"
```
### Средни задачки
**Задача 4**
Имплементирайте базовия клас `SchedulingSoftware`, със следните член функции
- `bool schedulePerson(Person* p);` Записва че дадения човек трябва да бъде вкаран в работния софтуер
- `Person* getNext();` Взима следващия човек който ще работи
**Задача 5**
Имплементирайте класа `QueueScheduler`, който всеки път като се извика `getNext()` връща човека най-напред в опашката и след това го поставя най-отзад.

Пример:
```c++
QueueScheduler qs;
qs.schedulePerson(&pt);
qs.schedulePerson(&ct);
qs.getNext() // Output: pt
qs.getNext() // Output: ct
qs.getNext() // Output: pt
```
**Задача 6**
Имплементирайте класа `RandomSchduler`, който всеки път като се извика `getNext()` връща случаен човек от добавените хора

Пример:
```c++
RandomSchduler rs;
rs.schedulePerson(&pt);
rs.schedulePerson(&ct);
rs.getNext() // Output: ct
rs.getNext() // Output: ct
rs.getNext() // Output: pt
```
### Трудни задачки
**Задача 7**
Променете класовете за работници така че да има работници с приоритет.
```c++
PrioritisedWorker w1(5), w2(1);
w1.getPriority(); // Output: 5
```
**Задача 8**
Напратете клас `PriorityScheduler`, който винаги избира работника с най-висок приоритет, като един работник е взет той се маха от списъка от работници.
```c++
PriorityScheduler ps;
ps.schedulePerson(&w2); 
ps.schedulePerson(&w1);
ps.getNext() // Output: w1
ps.getNext() // Output: w2
```
**Задача 9**
Имплементирайте, конструктор, деструктор, копи конструктор, move семантики и operator[] за класа `PriorityScheduler`
