#include "Necromancer.h"

#include <cstdlib>

void Necromancer::attack(Player& target)
{
	Mage::attack(target);

	if (armySize == 0)
	{
		return;
	}

	int selected = rand() % this->armySize;
	this->army[selected]->attack(target);

	if (target.isDead()) 
	{
		this->addToArmy(target);
	}
}
