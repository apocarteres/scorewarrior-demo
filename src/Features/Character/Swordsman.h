
#ifndef SWORDSMAN_H
#define SWORDSMAN_H
#include "../../Core/Character.h"
#include "../Intention/MeleeAttack.h"
#include "Core/Creature.h"

namespace sw::demo
{
	class Swordsman : public Character
	{
	public:
		Swordsman(uint32_t id, uint32_t hp, uint32_t power) :
				Character(id, "Swordsman", hp, true, 1, true, true)
		{
			intentions.push_back(std::make_unique<MeleeAttack>(power, creature));
		}
	};
}

#endif	//SWORDSMAN_H
