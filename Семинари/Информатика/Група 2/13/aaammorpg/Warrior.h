#pragma once

#include "Player.h"

class Warrior :
    public Player
{
private:
    unsigned shield;

public:
    virtual ~Warrior() = default;

    virtual void handle_attack(unsigned power) override;
};

