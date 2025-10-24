
#include "Creature.h"

using namespace sw::demo;

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
	return remoteAttackable;
}

bool Creature::isMeleeAttackable() const
{
	return meleeAttackable;
}

bool Creature::isRigid() const
{
	return rigid;
}

bool Creature::takeDamage(int damage)
{
	if (hp < 1 || hp < damage)
	{
		hp = 0;
		return false;
	}
	hp -= damage;
	return true;
}

bool Creature::restoreHp(int spirit)
{
	if (hp == maxHp)
	{
		return false;
	}
	hp+= spirit;
	if (hp > maxHp)
	{
		hp = maxHp;
	}
	return true;
}
