
#ifndef EXPLOSION_H
#define EXPLOSION_H
#include "Core/Intention/Intention.h"
#include "Core/Map/Map.h"
#include "Core/Creature.h"

namespace sw::demo
{
	class Explosion final : public Intention
	{
		int power;
		int activationRange;
		int damageRange;
		bool armed;

	public:
		Explosion(int power, int activationRange, int damageRange, const CreaturePtr& creature) :
				Intention(creature),
				power(power),
				activationRange(activationRange),
				damageRange(damageRange),
				armed(false)
		{}

		bool exec(uint32_t tick, map::Map* map, CreaturesContainer creatures) override;
	};
}
#endif	//EXPLOSION_H
