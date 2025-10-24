
#include "Creature.h"

std::string Creature::getName() const
{
	return name;
}

uint32_t Creature::getId() const
{
	return id;
}

int Creature::getHp() const
{
	return hp;
}

bool Creature::isRemoteAttackable() const
{
	return is_remote_attackable;
}

bool Creature::isMeleeAttackable() const
{
	return is_melee_attackable;
}

bool Creature::isRigid() const
{
	return is_rigid;
}

bool Creature::takeDamage(int damage)
{
	if (hp <= 0)
	{
		return false;
	}
	hp -= damage;
	if (hp <= 0)
	{
		hp = 0;
		return false;
	}
	return true;
}
