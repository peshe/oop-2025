#pragma once

#include "Player.h"

class Mage :
    public Player
{
private:
    char* skill;
    double coeff;

public:
    virtual ~Mage();

    double getCoeff() const;

    virtual void attack(Player& target) override;
};

