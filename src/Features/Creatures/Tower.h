
#ifndef TOWER_H
#define TOWER_H
#include "Character.h"
#include "Core/Intention/RangedAttack.h"

#define MAX_TOWER_RANGE (5)

class Tower : public Character
{
public:
	Tower(uint32_t id, uint32_t hp, uint32_t power) :
			Character(id, "Tower", hp)
	{
		intentions.push_back(std::make_unique<RangedAttack>(power, MAX_TOWER_RANGE, creature));
	}
};

#endif	//TOWER_H
