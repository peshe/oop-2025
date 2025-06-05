#include <iostream>

struct Source;

struct Sink
{


    Source * source = nullptr;

    void notifyPlug(Source * s) 
    {
        source = s;
    }

    virtual void notifyUnplug()
    {
        source = 0;    
    }

    virtual float getConsumption() const = 0;

    virtual ~Sink()
    {        
    }
};


struct Device : public Sink
{
    float power = 0;
    bool on = false;

    Device(float power) : power(power) {}

    float getConsumption() const override { 
        if(on) 
            return power;
        else
            return 0;
     }

     void turnOn() {
        on = true;
     }
     void turnOff() {
        on = false;
     }
};

struct Source
{
    virtual void notifyConsumptionChange() = 0;
    virtual ~Source() {}
};

struct Socket : public Source
{

    float maxPower = 0;
    Sink * plugged = nullptr;

    Socket(float maxPower) : maxPower(maxPower)
    {
    }

    void plug(Sink & s)
    {
        if(s.getConsumption() <= maxPower)
        {
            s.notifyPlug(this);
            plugged = &s;
        }
        else
            {
                maxPower = 0;
                plugged = nullptr;
            }
    }

    void unplug(Sink & s)
    {
        plugged = nullptr;
    }

    
    float getConsumption() const
    {
        return plugged ? plugged->getConsumption() : 0;
    }

    void notifyConsumptionChange()
    {
        if(getConsumption() > maxPower)
        {
            maxPower = 0;
            if(plugged)
                plugged->notifyUnplug();
            plugged = nullptr;
        }
    }

};

struct Multisocket : public Sink, public Source
{

    Sink * sinks[10];

    float maxPower = 0;

    Multisocket(float MaxPower) : maxPower(maxPower)
    {
       for(size_t k = 0; k < 10; ++k)
            sinks[k] = 0;
    }

    void plug(Sink & s, size_t k)
    {
        if(&s != this)
        {
            if(getConsumption() + s.getConsumption() <= maxPower)
                sinks[k] = &s;
            else
            {
                for(size_t k = 0; k < 10; ++k)
                    sinks[k] = nullptr;
                maxPower = 0;
            }
        }
    }

    
    float getConsumption() const override
    {
        float consumption = 0;
        for(size_t k = 0; k < 10; ++k)
            if(sinks[k])
                consumption += sinks[k]->getConsumption();
        
        return consumption;
    }

    void notifyConsumptionChange()
    {
        if(getConsumption() > maxPower)
        {
            maxPower = 0;            
            for(size_t k = 0; k < 10; ++k)
            {
                if(sinks[k])
                {
                    sinks[k] -> notifyUnplug();
                    sinks[k] = nullptr;
                }
            }
        }
    }

};

struct Lamp : public Sink 
{
    float power;
    bool on = false;

    Lamp(float power) : power(power) {}

    float getConsumption() const override
    {
        return on ? power : 0;
    }

    void notifyUnplug() override
    {
        Sink::notifyUnplug();
        turnOff();
    }

    void turnOn() { on = true;  if(source) source->notifyConsumptionChange(); }
    void turnOff() { on = false; }

    bool status() const {return on;}
    void printStatus() const { std::cout << (on?"ON":"off") << std::endl; }

};


int main()
{
    Lamp l(100);
    Socket s(150);

    s.plug(l);

    l.printStatus();

    l.turnOn();

    l.printStatus();

}
