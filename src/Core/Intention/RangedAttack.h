
#ifndef RANGEDATTACK_H
#define RANGEDATTACK_H
#include "Intention.h"

namespace sw::demo
{
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

		bool exec(Map* map, std::unordered_map<uint32_t, CreaturePtr> creatures) override;
	};
}

#endif	//RANGEDATTACK_H
