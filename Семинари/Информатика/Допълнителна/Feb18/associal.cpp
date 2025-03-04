#include <cstddef>
#include <algorithm>
#include <iostream>


// връща стойността и индекса на елемнтът с най-голяма стойност в d
void max_idx_val(size_t d[], size_t seat_count, size_t & idx, size_t & val)
{
    idx = 0;
    val = d[0];
    for(size_t i = 1; i < seat_count; ++i)
    {
        if(d[i] > val)
        {
            idx = i;
            val = d[i];
        }
    }
}

// разстояние между столове
size_t distance(size_t a, size_t b)
{
    return std::abs(int(a)-int(b));
}

// намира най-близкия зает стол
size_t min_distance(bool seats[], size_t seat_count, size_t idx)
{
    size_t cur_min = seat_count;
    for(size_t i = 0; i < seat_count; ++i)
    {
        if(seats[i])
            cur_min = std::min(cur_min, distance(i,idx));

    }
    return cur_min;
}


size_t place_new_programmer(bool seats[], size_t seat_count)
{
    size_t * distances = new size_t[seat_count];

    if(distances == nullptr) { /* нещо */}

    for(size_t i = 0; i < seat_count; i++)
    {
        distances[i] = min_distance(seats, seat_count, i);
    }

    size_t idx_max, max_val;
    max_idx_val(distances, seat_count, idx_max, max_val);


    size_t rtn = -1;
    if(max_val < 2)
        rtn = size_t(-1);
    else
    {
        seats[idx_max]=true;
        rtn = idx_max;
    }


    delete[] distances;
    return rtn;

}


void print_seated(bool seats[], size_t seat_count)
{
    for(size_t idx = 0; idx < seat_count; ++idx)
    {
        std::cout<<seats[idx];
    }
    std::cout << std::endl;
}

int main()
{
    bool seats[5];

    for(size_t initial = 0; initial < 5; ++initial)
    {

        std::cout << std::endl;
        for(size_t x = 0; x < 5; ++x) seats[x] = false;
        seats[initial] = true;

        
        print_seated(seats, 5);    
        size_t answer = -1;
        do {
            answer = place_new_programmer(seats, 5);
            if(answer != size_t(-1))
                print_seated(seats, 5);    
        }
        while(answer != size_t(-1));

        std::cout << initial << std::endl;
    
    }

    return 0;
}