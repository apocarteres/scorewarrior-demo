
#ifndef EXPLOSION_H
#define EXPLOSION_H
#include "Core/Creature.h"
#include "Core/Map.h"
#include "Intention.h"

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

		bool exec(Map* map, std::unordered_map<uint32_t, CreaturePtr> creatures) override;
	};
}
#endif	//EXPLOSION_H
