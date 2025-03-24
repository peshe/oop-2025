#include <iostream>
#include <iomanip>
#include <cassert>

/* Конструктор
    *   Конструкторите са специални методи, които се извикват автоматично при създаването на обект от даден клас.
        Те се използват за инициализация на данните на обекта.

    *   Конструкторите не създават обекти, а инициализират обектите.
        Компилаторът заделя паметта за обекта преди да извика конструктора.
        Чак след това се извиква конструктора върху неинициализирания обект.

    *   Конструкторите нямат тип на връщане и се дефинират със същото име като класа.
        Конструкторите могат да бъдат с параметри или без параметри.
        Конструкторът по подразбиране е конструктор, който няма параметри.

    *   Ако няма дефиниран конструктор, компилаторът автоматично създава конструктор по подразбиране.
        Ако има дефиниран конструктор с параметри, компилаторът не създава конструктор по подразбиране.

    *   Конструкторите имат "member initializer list", която се използва за инициализация на член-данните на класа.
        "Member initializer list" се състои от списък с имената на член-данните на класа, следвани от скоби и стойности.
        Този списък се използва за инициализация на член-данните преди тялото на конструктора да се изпълни.
    
    *   Инициализацията на член-данните е в следния ред:
        1. Ако има "member initializer list", тя се изпълнява.
        2. Иначе ако при декларацията на член-данната има подадена стойност по подразбиране, тя се използва.
        3. Иначе се използва конструкторът по подразбиране на типа на член-данната.
*/

class Time {
public:
    Time(); // Конструктор по подразбиране.
    Time(std::uint16_t hours, std::uint16_t minutes, std::uint16_t seconds); // Конструктор с параметри.

    void addHours(std::uint16_t hours);
    void addMinutes(std::uint16_t minutes);
    void addSeconds(std::uint16_t seconds);

    void print();

private:
    std::uint16_t m_hours{};
    std::uint16_t m_minutes{};
    std::uint16_t m_seconds{};
};

int main() {
    Time defaultConstructorTime1; // Извиква се конструкторът без параметри (конструктор по подразбиране).
    Time defaultConstructorTime2 = Time(); // Извиква се конструкторът без параметри (конструктор по подразбиране).
    Time defaultConstructorTime3{}; // Извиква се конструкторът без параметри (конструктор по подразбиране).

    Time constructorTime1(10, 30, 45); // Извиква се конструкторът с параметри.
    Time constructorTime2 = Time(10, 30, 45); // Извиква се конструкторът с параметри.
    Time constructorTime3{ 10, 30, 45 }; // Извиква се конструкторът с параметри.

    Time time{ 10, 30, 45 };

    time.print();

    time.addSeconds(327);

    time.print();

    return 0;
}

// Примерна употреба на member initializer list.
Time::Time() : m_hours(0), m_minutes{0}, m_seconds{0} {}

Time::Time(std::uint16_t hours, std::uint16_t minutes, std::uint16_t seconds)
    :   m_hours(hours),
        m_minutes(minutes),
        m_seconds(seconds) {
    assert(hours < 24);
    assert(minutes < 60);
    assert(seconds < 60);

    // this->m_hours = hours; // Важно: това не е инициализация, а присвояване.
}

void Time::addHours(std::uint16_t hours) {
    this->m_hours += hours;
}

void Time::addMinutes(std::uint16_t minutes) {
    this->m_minutes += minutes;

    this->addHours(this->m_minutes / 60);
    this->m_minutes %= 60;
}

void Time::addSeconds(std::uint16_t seconds) {
    this->m_seconds += seconds;

    this->addMinutes(this->m_seconds / 60);
    this->m_seconds %= 60;
}

void Time::print() {
    std::cout << std::setw(2) << std::setfill('0');

    std::cout << this->m_hours << ":" << this->m_minutes << ":" << this->m_seconds << std::endl;

    std::cout << std::setw(0) << std::setfill(' ');
}
