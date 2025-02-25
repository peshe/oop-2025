/*
 Petar Armyanov  @ FMI 2025

 Function pointers.

***************
 Accumulate algorithm over array
 Map function on a string
 Simple interactive calculator
*/

#include <iostream>
#include <cassert>
using std::cin;
using std::cout;
using std::endl;

typedef int (*binFun)(int, int);
int accumulate(int a[], int n, const binFun fun, int start)
{
    for (int i = 0; i < n; ++i) {
        start = fun(start, a[i]);
    }
    return start;
}

/* **********************************************************/

typedef char (*charFunPtr)(char);
void processString(char* text, const charFunPtr processor)
{
    while (*text) {
        *text = processor(*text);
        ++text;
    }
}

char toUpper(char c)
{
    if (c >= 'a' && c <= 'z') {
        return c - 'a' + 'A';
    }
    return c;
}

char toLower(char c)
{
    if (c >= 'A' && c <= 'Z') {
        return c - 'A' + 'a';
    }
    return c;
}

/* **********************************************************/

int sum(int a, int b)
{
    return a+b;
}

int sub(int a, int b)
{
    return a-b;
}

int mul(int a, int b)
{
    return a*b;
}

int divide(int a, int b)
{
    if (b) return a/b;
    return 0;
}

int mod(int a, int b)
{
    if (b) return a%b;
    return 0;
}

int eq(int a, int b)
{
    return a==b;
}

int gt(int a, int b)
{
    return a > b;
}

int lt(int a, int b)
{
    return gt(b, a);
}

int let(int a, int b)
{
    //return !gt(a, b);
    return eq(a, b) || lt (a, b);
}

int print(int a, int b)
{
    cout << a << ' ' << b;
    return 0;
}

static const char   oper[]      = {'+', '-', '*',    '/', '%', '=', '>', '<', 'l'};
static const binFun functions[] = {sum, sub, mul, divide, mod,  eq,  gt,  lt, let};
static const int    arraySize   = sizeof(oper)/sizeof(oper[0]);

int error(int, int)
{
    cout << "unknown operation!\n";
    return -1;
}

binFun selectFun(char operation)
{
    for (int i = 0; i < arraySize; ++i) {
        if (oper[i] == operation) {
            return functions[i];
        }
    }
    return error;
}

int calc(int a, int b, char operation)
{
    binFun function = selectFun(operation);
    assert(function != nullptr);

    return function(a, b);
}

int posCnt(int res, int x)
{
    return x > 0 ? res + 1 : res;
}

int main()
{
/*
    int arr[] = {1, 2, 3, 0, 5, 0, -4, -5};
    const size_t size = sizeof(arr)/sizeof(arr[0]);

    cout << accumulate(arr, 5, sum, 0) << endl;
    cout << accumulate(arr, 5, mul, 1) << endl;
    cout << accumulate(arr, size, posCnt, 0) << endl;
    cout << accumulate(arr, size, [](int a, int b){return a<b?a:b;}, arr[0]) << endl;
*/
/*
    while (rand()%5) {
        char text[] = "I love to point things. Even functions ;)";
        switch(rand()%3) {
            case 0:    processString(text, toUpper);
            break;
            case 1:    processString(text, toLower);
            break;
            case 2:    processString(text, [](char a){cout << a; return a;});
            break;
        }
        cout << text << endl;
    }
*/

    char c;
    do {
        int x, y;
        cin >> x >> c >> y;
        if (c == 'e') break;
        cout << calc (x, y, c) << "\n";
    } while (c != 'e' && cin);

    return 0;
}
