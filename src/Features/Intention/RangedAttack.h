
#ifndef RANGEDATTACK_H
#define RANGEDATTACK_H
#include "Core/Intention/Intention.h"

namespace sw::demo
{
	#define MIN_ATTACK_RANGE (2)

	class RangedAttack final : public Intention
	{
		int power;
		int range;

	public:
		RangedAttack(int power, int range, const CreaturePtr& creature) :
				Intention(creature),
				power(power),
				range(range)
		{}

		bool exec(uint32_t tick, map::Map* map, const CreaturesContainer& creatures) override;
	};
}

#endif	//RANGEDATTACK_H
