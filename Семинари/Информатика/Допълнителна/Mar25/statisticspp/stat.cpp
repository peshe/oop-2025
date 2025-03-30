#include <algorithm>
#include <iostream>

#include <limits>

class Stat 
{
private:
    float cur_sum = 0;
    int n = 0;
    float cur_max = 0;

    float * all = nullptr;
    int capacity = 0;

public:
    Stat()
    {
        capacity = 5;
        all = new float[capacity];
    }

    ~Stat()
    {
        delete[] all;
        all = nullptr;
        capacity = n = cur_sum = cur_max = 0;
    }

    Stat & add(float x)
    {
        cur_sum += x;
        if(0 == n)
            cur_max = x;
        else
            cur_max = std::max(cur_max, x);

        if(n >= capacity)
        {
            capacity *= 2;
            float * new_all = new float[capacity];
            for(int k = 0; k < n; ++k)
                new_all[k] = all[k];
            
            delete[] all;
            all = new_all;
        }    

        all[n] = x;
        n++;    
        return *this;
    }

    void remove_last()
    {
        // TBD
    }

    float mean()
    {
        return cur_sum / n;
    }


    float max()
    {
        return cur_max;
    }

};

int main()
{
    Stat s;
    s.add(3).add(5);

    std::cout << "max=" << s.max() << " mean=" << s.mean() << std::endl;
}



