#pragma once
#include "appliance.hpp"

class Socket
{
private:
    Appliance **sockets;
    unsigned currAmp;
    unsigned maxAmp;
    const unsigned devCap;
    bool burnedOut;

public:
    Socket(unsigned maxDevices, unsigned maxAmp);
    ~Socket();
    Socket(const Socket &other);
    Socket &operator=(const Socket &other) = delete;
    Appliance *operator[](const unsigned index) const;
    unsigned getSize() const { return devCap; };
    bool turnOnOffDevice(unsigned index, bool val);
    bool isInRange();
    bool plugInDevice(Appliance &dev);
    void print() const;
};