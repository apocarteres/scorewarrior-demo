
#ifndef TOWER_H
#define TOWER_H
#include "Character.h"
#include "Core/Intention/RangedAttack.h"

#define MAX_TOWER_RANGE (5)

class Tower final : public Character
{
public:
	Tower(uint32_t id, uint32_t hp, uint32_t power) :
			Character(id, "Tower", hp, true, 0, true, true)
	{
		intentions.push_back(std::make_unique<RangedAttack>(power, MAX_TOWER_RANGE, creature));
	}
};

#endif	//TOWER_H
