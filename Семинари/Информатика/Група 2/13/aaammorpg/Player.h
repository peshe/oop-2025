#pragma once

#include "Point.h"

enum class Weapon {
	Sword,
	Wand,
	Staff,
	Axe
};

class Mage;

class Player
{
private:
	char* name;
	Point position;
	Weapon weapon;
	unsigned attack_damage;

protected:
	unsigned health;

public:
	virtual ~Player();

	void useMageSkill(const Mage& m);
	bool isDead() const;

	virtual void move(Point p);
	virtual void attack(Player& target);
	virtual void handle_attack(unsigned power);
	virtual unsigned get_attack_power() const;
};

#include "Mage.h"

