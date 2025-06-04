#pragma once

#include "Mage.h"

class Necromancer :
    public Mage
{
private:
    int armySize;
    Player** army;

    void addToArmy(const Player& p);

public:
    virtual ~Necromancer();

    virtual void attack(Player& target) override;
};

