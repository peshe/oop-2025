#include "time.hpp"

int main()
{
    Time t;
    t.print();
    t.setMin(47);
    t.setSec(14);
    t.print();
    Time t2;
    t2.setMin(17);
    t2.setSec(57);
    t2.print();
    t.addTime(t2);
    t.print();
    return 0;
}
