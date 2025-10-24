
#ifndef HUNTER_H
#define HUNTER_H
#include "Character.h"
#include "Core/Intention/MeleeAttack.h"
#include "Core/Intention/RangedAttack.h"

class Hunter : public Character
{
public:
	Hunter(uint32_t id, uint32_t hp, int strength, int range, int agility) :
			Character(id, "Hunter", hp)
	{
		intentions.push_back(std::make_unique<RangedAttack>(agility, strength, range, creature));
		intentions.push_back(std::make_unique<MeleeAttack>(strength, creature));
	}
};

#endif	//HUNTER_H
