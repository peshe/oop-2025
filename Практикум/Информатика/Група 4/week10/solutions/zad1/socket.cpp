#include "socket.hpp"
#include <iostream>

Socket::Socket(unsigned maxDevices, unsigned maxAmp) : devCap(maxDevices), maxAmp(maxAmp), burnedOut(false)
{
    currAmp = 0;
    try
    {
        sockets = new Appliance *[devCap]
        { nullptr };
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }
}

Socket::~Socket()
{
    delete[] sockets;
}

Socket::Socket(const Socket &other) : devCap(other.devCap), maxAmp(other.maxAmp), burnedOut(false)
{
    currAmp = 0;
    try
    {
        sockets = new Appliance *[devCap]
        { nullptr };
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }
}

Appliance *Socket::operator[](const unsigned index) const
{
    if (index >= devCap)
    {
        return nullptr;
    }
    return sockets[index];
}

bool Socket::turnOnOffDevice(unsigned index, bool val)
{
    if (!sockets[index])
    {
        return false;
    }
    sockets[index]->setTurnedOn(val);
    if (!val)
    {
        currAmp = currAmp > sockets[index]->getPower() ? currAmp - sockets[index]->getPower() : 0;
        return true;
    }
    else
    {
        currAmp += sockets[index]->getPower();
        return isInRange();
    }
}

bool Socket::isInRange()
{
    if (currAmp > maxAmp)
    {
        burnedOut = true;
        std::cout << "Burned out!!!!" << std::endl;
        for (size_t i = 0; i < devCap; i++)
        {
            if (sockets[i])
            {
                sockets[i]->setTurnedOn(false);
                sockets[i]->setSocket(nullptr);
            }
            sockets[i] = nullptr;
        }
        return false;
    }
    return true;
}

bool Socket::plugInDevice(Appliance &dev)
{
    if (burnedOut == true || dev.getPluggedIn() == true)
    {
        std::cout << "Burned out or device already plugged in" << std::endl;
        return false;
    }
    for (size_t i = 0; i < devCap; i++)
    {
        if (sockets[i] == nullptr)
        {
            sockets[i] = &dev;
            dev.setSocket(this);
            return true;
        }
    }
    return false;
}

void Socket::print() const
{
    std::cout << "Socket: " << std::endl;
    std::cout << "Max Amp: " << maxAmp << std::endl;
    std::cout << "Current Amp: " << currAmp << std::endl;
    std::cout << "Burned Out: " << (burnedOut ? "Yes" : "No") << std::endl;
    std::cout << "Devices: " << std::endl;
    for (size_t i = 0; i < devCap; i++)
    {
        if (sockets[i])
        {
            std::cout << *sockets[i] << std::endl;
        }
    }
}
