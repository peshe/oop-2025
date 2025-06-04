#include "Mage.h"

void Mage::attack(Player& target)
{
	target.useMageSkill(*this);

	target.handle_attack(this->get_attack_power());
}
