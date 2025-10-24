
#ifndef TOWER_H
#define TOWER_H
#include "../../Core/Character.h"
#include "../Intention/RangedAttack.h"

#define MAX_TOWER_RANGE (5)

namespace sw::demo
{
	class Tower final : public Character
	{
	public:
		Tower(uint32_t id, uint32_t hp, uint32_t power) :
				Character(Creature{id, hp, true, true, true, "Tower"}, 0)
		{
			intentions.push_back(std::make_unique<RangedAttack>(power, MAX_TOWER_RANGE, creature));
		}
	};
}

#endif	//TOWER_H
