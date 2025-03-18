#pragma once

#ifndef _TIME_HEADER_INCLUDED
#define _TIME_HEADER_INCLUDED

class Time
{
public:
    int getHour() { return seconds / 3600; }
    void setHour(int h);
    
    int getMin() { return seconds % 3600 / 60; }
    void setMin(int m);
    
    int getSec() { return seconds % 60; }
    void setSec(int s);

    void print();
    void addTime(Time& t);

private:
    int seconds = 0;
};

#endif //_TIME_HEADER_INCLUDED
