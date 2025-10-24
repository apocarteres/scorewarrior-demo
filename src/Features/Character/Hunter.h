
#ifndef HUNTER_H
#define HUNTER_H
#include "../../Core/Character.h"
#include "../Intention/MeleeAttack.h"
#include "../Intention/RangedAttack.h"

namespace sw::demo
{
	class Hunter final : public Character
	{
	public:
		Hunter(uint32_t id, uint32_t hp, uint32_t strength, uint32_t range, uint32_t agility) :
				Character(id, "Hunter", hp, true, 1, true, true)
		{
			intentions.push_back(std::make_unique<RangedAttack>(agility, range, creature));
			intentions.push_back(std::make_unique<MeleeAttack>(strength, creature));
		}
	};
}

#endif	//HUNTER_H
