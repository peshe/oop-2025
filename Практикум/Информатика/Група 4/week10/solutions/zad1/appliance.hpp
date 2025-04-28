#pragma once
#include <fstream>

class Socket;

class Appliance
{
private:
    char *brand;
    char *description;
    unsigned power;
    bool pluggedIn;
    bool turnedOn;
    Socket *sck;
    const unsigned id;
    static unsigned nextID;
    void copy(const Appliance &other);

public:
    Appliance(const char *brand = "", const char *description = "", unsigned power = 0);
    Appliance(std::istream &is);
    ~Appliance();
    Appliance(const Appliance &other);
    Appliance &operator=(const Appliance &other);
    bool operator==(const Appliance &other) const;
    bool operator!=(const Appliance &other) const;
    bool operator>(const Appliance &other) const;
    bool operator<(const Appliance &other) const;
    friend std::ostream &operator<<(std::ostream &of, const Appliance &obj);
    friend std::istream &operator>>(std::istream &is, Appliance &obj);

    void writeFile(char *filename) const;
    void readFile(char *filename);

    unsigned getPower() const { return power; };
    bool getTurnedOn() const { return turnedOn; };
    void setTurnedOn(bool val);
    bool getPluggedIn() const { return pluggedIn; };
    const Socket *getSocket() const { return sck; };
    void setSocket(Socket *socket)
    {
        socket == nullptr ? pluggedIn = false : pluggedIn = true;
        sck = socket;
    };
};
