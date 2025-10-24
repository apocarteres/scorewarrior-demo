
#ifndef HUNTER_H
#define HUNTER_H
#include <Core/Character.h>
#include <Features/Intention/MeleeAttack.h>
#include <Features/Intention/RangedAttack.h>

namespace sw::demo
{
	class Hunter final : public Character
	{
	public:
		Hunter(uint32_t id, uint32_t hp, uint32_t strength, uint32_t range, uint32_t agility) :
				Character(Creature{id, hp, true, true, true, "Hunter"}, 1)
		{
			intentions.push_back(std::make_unique<RangedAttack>(agility, range, creature));
			intentions.push_back(std::make_unique<MeleeAttack>(strength, creature));
		}
	};
}

#endif	//HUNTER_H
