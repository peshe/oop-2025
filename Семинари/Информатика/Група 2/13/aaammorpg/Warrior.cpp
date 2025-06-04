#include "Warrior.h"

void Warrior::handle_attack(unsigned power)
{
	if (this->shield < power)
	{
		this->shield = 0;
		this->health -= power - this->shield;
	}
	else
	{
		this->shield -= power;
	}
}
