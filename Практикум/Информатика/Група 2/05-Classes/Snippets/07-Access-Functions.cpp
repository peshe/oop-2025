#include <iostream>
#include <cassert>
#include <iomanip>

/*  Функции за достъп
    *   Функции за достъп са прости публични методи, която работа е да взимат или
        задават стойност на private член-данните на класа.
    
    *   Има 2 вида такива функции:
        1. Функции за взимане на стойност - getters (селектори).
        2. Функции за задаване на стойност - setters (мутатори).

    *   Гетърите трябва да връщат стойност (ако създаването на копие не е твърде скъпо) или
        константна референция (ако създаването на копие е твърде скъпо).
*/

/*  Капсулация
    Капсулацията е принцип на ООП (един от 4те), който предпазва данните на класа от неправилно
    използване. Тя се постига чрез дефинирането на член-данните на класа като private
    и предоставянето на публични методи за достъп до тях.
*/

class Time {
    public:
        Time();
        Time(std::uint16_t hours, std::uint16_t minutes, std::uint16_t seconds);

        std::uint16_t getHours();
        void setHours(std::uint16_t hours);

        std::uint16_t getMinutes();
        void setMinutes(std::uint16_t minutes);

        std::uint16_t getSeconds();
        void setSeconds(std::uint16_t seconds);

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
    return 0;
}

Time::Time() : m_hours(0), m_minutes{0}, m_seconds{0} {}

Time::Time(std::uint16_t hours, std::uint16_t minutes, std::uint16_t seconds)
    :   m_hours(hours),
        m_minutes(minutes),
        m_seconds(seconds) {
    assert(hours < 24);
    assert(minutes < 60);
    assert(seconds < 60);
}

std::uint16_t Time::getHours() {
    return this->m_hours;
}

void Time::setHours(std::uint16_t hours) {
    this->m_hours = hours;
}

std::uint16_t Time::getMinutes() {
    return this->m_minutes;
}

void Time::setMinutes(std::uint16_t minutes) {
    this->m_minutes = minutes;
}

std::uint16_t Time::getSeconds() {
    return this->m_seconds;
}

void Time::setSeconds(std::uint16_t seconds) {
    this->m_seconds = seconds;
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
