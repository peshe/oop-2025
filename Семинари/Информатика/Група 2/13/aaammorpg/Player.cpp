#include "Player.h"

void Player::useMageSkill(const Mage& m)
{
	this->health *= m.getCoeff();
}
