
#include "MeleeAttack.h"

using namespace sw::demo;

bool MeleeAttack::exec(uint32_t tick, map::Map* map, std::unordered_map<uint32_t, CreaturePtr> creatures)
{
	auto neighborIds = map->lookupNeighbors(creature->getId(), 1);
	for (auto& neighborId : neighborIds)
	{
		auto neighbor = creatures[neighborId];
		if (neighbor->isMeleeAttackable())
		{
			if (neighbor->takeDamage(power))
			{
				logDamageDealt(tick, creature, neighbor, power);
				return true;
			}
		}
	}
	return false;
}
