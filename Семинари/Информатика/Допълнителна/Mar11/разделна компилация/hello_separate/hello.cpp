#include <iostream>

extern char * world();

using namespace std;

int main()
{
    cout << "Hello " << world()  << endl;
}