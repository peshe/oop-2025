#pragma once

class LimitedInstances
{
    
private:
    LimitedInstances(int val = 42)
        : data(val)
    {
        if (!LimitedInstances::canCreateInstance(val))
            throw "Too many objects!\n";

        usedResources += val;
    }

    LimitedInstances(const LimitedInstances& other)
        : LimitedInstances(other.data)
    { }

    ~LimitedInstances()
    {
        LimitedInstances::usedResources -= this->data;
    }


    static bool canCreateInstance(unsigned newRes)
    {
        return usedResources + newRes <= MaxResources;
    }

private:
    int data;

    static unsigned usedResources;
    static const unsigned MaxResources;

    static LimitedInstances* theObj;
};
