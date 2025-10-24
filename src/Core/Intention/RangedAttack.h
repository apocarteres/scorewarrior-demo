
#ifndef RANGEDATTACK_H
#define RANGEDATTACK_H
#include "Intention.h"

class RangedAttack : public Intention
{
	int agility;
	int strength;
	int range;

public:
	RangedAttack(int agility, int strength, int range, const CreaturePtr& creature) :
			Intention(creature),
			agility(agility),
			strength(strength),
			range(range)
	{}

	bool exec(Map* map, std::unordered_map<uint32_t, CreaturePtr> creatures) override;
};



#endif	//RANGEDATTACK_H
