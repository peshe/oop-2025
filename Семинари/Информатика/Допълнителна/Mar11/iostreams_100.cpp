#include <iostream>
#include <fstream>

#include "printstreamstate.h"

using namespace std;


int main()
{

    // //ifstream ifs("bulgarian.txt");
    // ifstream ifs("digits.txt");
    // // ifstream ifs;

    // printstreamstate(ifs);

    // int n=-1; ifs >> n; cout << n << endl;

    // printstreamstate(ifs);

    // ifs >> n; cout << n << endl;

    // printstreamstate(ifs);

    ifstream ifs2("digits.txt");

    while(ifs2.good())
    {
        int c = ifs2.get();
        if(!ifs2.good())
            break;
        cout.put(c);
    }

}