/*
 Petar Armyanov  @ FMI 2025

 Introduction to preprocessor.
*/

#include <iostream>
#include <cassert>

using std::cout;
using std::endl;

#define MIN(a, b) ((a)<(b)?(a):(b))

#ifdef DEBUG
#   define dbgPrint(fun, p1, p2) cout << __LINE__ << " : " << fun"(" << p1 << ", " << p2 << ")" << endl
#else
#   define dbgPrint
#endif

static double power(double x, unsigned n)
{
    dbgPrint("power", x, n);
    assert("power input parametrer" && n < 10);

    if (n == 0)
        return 1;

    double p2 = power(x, n/2);

    dbgPrint("power", n, p2);

    if (n%2 == 1)
        return x * p2 * p2;
    else
        return p2 * p2;
}

static double sqrt(double x)
{
    assert (x >= 0);
    double result = 0;
    //.......
    assert (result >= 0);
    assert ("Correct result" && abs(result*result - x) < 0.0001);
    return result;
}

int main()
{
    int x = 5;
    cout << MIN(x, x+=5) << endl;
    cout << power(2, 100) << endl;
    return 0;
}
