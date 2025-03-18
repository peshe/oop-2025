#include <iostream>

#include "stat.h"


int main()
{
    Stat * stat = stat_empty();

    for(float f = 1; f < 100; f = f + 1)
        stat_add(*stat,f);    

    std::cout << stat_mean(*stat) << std::endl;
    std::cout << stat_max(*stat) << std::endl;

    close_handle(stat);

    return 0;
}