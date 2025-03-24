#include "time.hpp"

#include <cmath>
#include <iostream>

void Time::setHour(int h)
{
    h = abs(h) % 24;
    this->seconds = h*3600 + this->seconds%3600;
}

void Time::setMin(int m)
{
    m = abs(m) % 60;
    this->seconds = m * 60 + seconds / 3600 * 3600 + seconds % 60;
}

void Time::setSec(int s)
{
    s = abs(s) % 60;
    this->seconds = seconds - getSec() + s;
}

void Time::print()
{ 
    std::cout << this->getHour() << ":"
        << this->getMin() << ":"
        << this->getSec() << "\n";
}

void Time::addTime(Time& t)
{
    seconds += t.seconds;
}
