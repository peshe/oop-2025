#include <iostream>
#include <string>
#include <stdexcept>
#include <cstdlib>
#include <ctime>
#include <vector>

struct Point
{
	int x, y;
};

Point operator-(Point a, Point b)
{
	return {a.x - b.x, a.y - b.y};
}

std::ostream& operator<<(std::ostream& os, const Point& p)
{
	return os << '(' << p.x << ", " << p.y << ')';
}

enum class Weapon
{
	SWORD,
	WAND,
	STAFF,
	AXE,
};

const char* to_string(Weapon w)
{
	switch(w)
	{
	case Weapon::SWORD:
		return "Sword";
	case Weapon::WAND:
		return "Wand";
	case Weapon::STAFF:
		return "Staff";
	case Weapon::AXE:
		return "Axe";
	default:
		throw std::invalid_argument("unknown weapon");
	}
}

long long random_pseudo_uniform(long long from, long long to)
{
	long long interval_len = to - from + 1;
	return rand() % interval_len + from;
}

class Player
{
	unsigned health;
	const std::string name;
	Point pos;
	Weapon weapon;
	unsigned attack_damage;

	bool adjacent(const Player& p) const noexcept
	{
		Point dist = pos - p.pos;
		dist = {std::abs(dist.x), std::abs(dist.y)};
		return dist.x + dist.y == 1; // (0, 1) or (1, 0)
	}
protected:
	static unsigned absorb_damage_relative(unsigned& target, unsigned dmg)
	{
		unsigned remaining_dmg = dmg - target;
		if(dmg <= target)
		{
			target -= dmg;
			return 0;
		}
		target = 0;
		return remaining_dmg;
	}
public:
	Player(unsigned health, const std::string& name, Point pos, Weapon weapon, unsigned attack_damage):
		health(health), name(name), pos(pos), weapon(weapon), attack_damage(attack_damage > 0 ? attack_damage : throw std::invalid_argument("attack damage must be positive")) {}

	void move(Point pos) noexcept
	{
		this->pos = pos;
	}
	unsigned attack_power() const noexcept
	{
		return attack_damage;
	}
	unsigned Health() const noexcept
	{
		return health;
	}
	virtual std::ostream& print(std::ostream& os) const
	{
		os << "Health: " << health << '\n';
		os << "Name: " << name << '\n';
		os << "Position: " << pos << '\n';
		os << "Weapon: " << to_string(weapon) << '\n';
		os << "Attack damage: " << attack_damage << '\n';
		return os;
	}
	virtual ~Player() = default;
	Player(Player&& other) = default;
	Player(const Player& other) = default;
	Player& operator=(const Player& other) = delete; // even without this line, the copy assignment operator is implicitly declared as deleted (because of the const member `name`)
	Player& operator=(Player&& other) = delete; // same for the move assignment

	bool handle_attack(Player& attacker)
	{
		if(!adjacent(attacker)) return false;
		attacker.attack(*this);
		return true;
	}
	virtual void attack(Player& target)
	{
		target.absorb_damage(attack_power());
	}
	virtual unsigned absorb_damage(unsigned dmg)
	{
		return absorb_damage_relative(health, dmg);
	}
	[[nodiscard]] virtual Player* clone() const
	{
		return new Player(*this);
	}
};

std::ostream& operator<<(std::ostream& os, const Player& p)
{
	return p.print(os);
}

class Warrior: public Player
{
	unsigned armor;
public:
	Warrior(unsigned health, const std::string& name, Point pos, Weapon weapon, unsigned attack_damage, unsigned armor):
		Player(health, name, pos, weapon, attack_damage), armor(armor) {}
	virtual std::ostream& print(std::ostream& os) const override
	{
		Player::print(os);
		os << "Armor: " << armor << '\n';
		return os;
	}
	virtual unsigned absorb_damage(unsigned dmg) override
	{
		unsigned remaining_dmg = absorb_damage_relative(armor, dmg);
		return Player::absorb_damage(remaining_dmg);
	}
	[[nodiscard]] virtual Warrior* clone() const override
	{
		return new Warrior(*this);
	}
};

class Mage: public Player
{
	std::string magic_ability;
	double coef;
public:
	Mage(unsigned health, const std::string& name, Point pos, Weapon weapon, unsigned attack_damage, const std::string& magic_ability, double coef):
		Player(health, name, pos, weapon, attack_damage), magic_ability(magic_ability), coef(coef > 0 && coef < 1 ? coef : throw std::invalid_argument("attack coefficient must be in (0, 1)")) {}
	virtual std::ostream& print(std::ostream& os) const override
	{
		Player::print(os);
		os << "Magic ability: " << magic_ability << '\n';
		os << "Attack coefficient: " << coef << '\n';
		return os;
	}
	virtual void attack(Player& target) override
	{
		target.Player::absorb_damage(coef * target.Health()); // or `target.absorb_damage(coef * target.Health())` if we want, e.g., the warrior to handle this attack
		target.absorb_damage(attack_power());
	}
	[[nodiscard]] virtual Mage* clone() const override
	{
		return new Mage(*this);
	}
};

typedef std::vector<Player*> PlayerVector;

class Necromancer: public Mage
{
	PlayerVector destroyed_players;

	void deallocate()
	{
		for(std::size_t i = 0; i < destroyed_players.size(); i++)
			delete destroyed_players[i];
	}
public:
	/*Necromancer(unsigned health, const std::string& name, Point pos, Weapon weapon, unsigned attack_damage, const std::string& magic_ability, double coef):
		Mage(health, name, pos, weapon, attack_damage, magic_ability, coef) {}*/
	using Mage::Mage;

	virtual void attack(Player& target) override
	{
		Mage::attack(target);
		if(!destroyed_players.empty())
		{
			std::size_t ind = random_pseudo_uniform(0, destroyed_players.size() - 1);
			destroyed_players[ind]->attack(target);
		}
		if(target.Health() == 0)
			destroyed_players.push_back(target.clone());
	}
	[[nodiscard]] virtual Necromancer* clone() const override
	{
		return new Necromancer(*this);
	}
	~Necromancer()
	{
		deallocate();
	}
	Necromancer(const Necromancer& other): Mage(other)
	{
		destroyed_players.reserve(other.destroyed_players.size());
		try
		{
			for(std::size_t i = 0; i < other.destroyed_players.size(); i++)
				destroyed_players.push_back(other.destroyed_players[i]->clone());
		}
		catch(...)
		{
			deallocate();
			throw;
		}
	}
	Necromancer(Necromancer&& other) = default;
};

int main()
{
	std::srand(std::time(nullptr));

	Mage m(1000, "", {0,0}, Weapon::AXE, 50, "asd", 0.3);
	Warrior w(10000, "", {-1,0}, Weapon::AXE, 10, 300);

	w.handle_attack(m);
	w.print(std::cout);
	m.print(std::cout);
	return 0;
}