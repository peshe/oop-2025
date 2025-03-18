#include <algorithm>
#include <iostream>

#include <limits>

struct Stat 
{
    float cur_sum;
    int n;
    float cur_max;

    float * all;
    int capacity;
};


Stat * stat_empty()
{
    Stat * s = new Stat;
    *s = {0,0,0, new float[10], 10};
    return s;
}

void stat_add(Stat & s, float x)
{
    s.cur_sum += x;
    if(0 == s.n)
        s.cur_max = x;
    else
        s.cur_max = std::max(s.cur_max, x);

    if(s.n >= s.capacity)
    {
        s.capacity *= 2;
        float * new_all = new float[s.capacity];
        for(int k = 0; k < s.n; ++k)
            new_all[k] = s.all[k];
        
        delete[] s.all;
        s.all = new_all;
    }    

    s.all[s.n] = x;

    s.n++;    
}

void stat_remove_last(Stat & s)
{

}

float stat_mean(const Stat & s)
{
    return s.cur_sum / s.n;
}


float stat_max(const Stat & s)
{
    return s.cur_max;
}

void close_handle(const Stat * s)
{
    delete[] s->all;
    delete s;
}

