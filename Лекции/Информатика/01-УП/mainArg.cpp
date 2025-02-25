/*
 Petar Armyanov  @ FMI 2025

 Main function with arguments
*/

#include <iostream>
#include <cstdlib>
using std::cout;
using std::endl;
using std::cin;

int main(int argc, const char* argv[])
{
    cout << argc << endl;

    for (int i = 0; argv[i]; ++i)
        cout << argv[i] << endl;

    // input and output redirection
    int x;
    cin >> x;
    cout << x << endl;
    std::cerr << "ERRor \n";
    std::clog << "Error 2";
    return 0;
}
