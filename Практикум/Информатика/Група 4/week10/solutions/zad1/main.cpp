#include "appliance.hpp"
#include "socket.hpp"
#include <iostream>
#include <vector>
#include <string>
#include <fstream>

int main()
{
    std::fstream ifstream("devices.txt");
    if (!ifstream)
    {
        return 0;
    }
    unsigned numOfDevices, i;
    ifstream >> numOfDevices >> i;
    ifstream.ignore();

    Appliance **devices = new Appliance *[numOfDevices];
    Socket socket1(numOfDevices, i);
    Socket socket2(numOfDevices, i);
    for (size_t i = 0; i < numOfDevices; i++)
    {
        Appliance *dev = new Appliance(ifstream);
        devices[i] = dev;
        if (i < numOfDevices / 2)
        {
            socket1.plugInDevice(*devices[i]);
        }
        else
        {
            socket2.plugInDevice(*devices[i]);
        }
    }
    socket1[0]->setTurnedOn(true);
    socket1[1]->setTurnedOn(true);
    socket2.plugInDevice(*devices[0]);
    socket1[2]->setTurnedOn(true);
    socket1.print();
    socket2.plugInDevice(*devices[0]);
    socket2.print();
    for (size_t i = 0; i < numOfDevices; i++)
    {
        delete devices[i];
    }

    ifstream.close();
    return 0;
}
