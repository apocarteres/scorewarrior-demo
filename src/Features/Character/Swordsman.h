
#ifndef SWORDSMAN_H
#define SWORDSMAN_H
#include "../../Core/Character.h"
#include "../Intention/MeleeAttack.h"
#include "Core/Creature.h"

namespace sw::demo
{
	class Swordsman final : public Character
	{
	public:
		Swordsman(uint32_t id, uint32_t hp, uint32_t power) :
				Character(Creature{id, hp, true, true, true, "Swordsman"}, 1)
		{
			intentions.push_back(std::make_unique<MeleeAttack>(power, creature));
		}
	};
}

#endif	//SWORDSMAN_H
