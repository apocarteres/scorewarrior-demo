
#include "MeleeAttack.h"

using namespace sw::demo;

bool MeleeAttack::exec(uint32_t tick, map::Map* map, const CreaturesContainer& creatures)
{
	auto neighborIds = map->lookupNeighbors(creature->getId(), 1);
	for (auto& neighborId : neighborIds)
	{
		const auto& neighbor = creatures.at(neighborId);
		if (!neighbor->isMeleeAttackable())
		{
			continue;
		}
		if (!neighbor->takeDamage(power))
		{
			continue;
		}
		logDamageDealt(tick, creature, neighbor, power);
		return true;
	}
	return false;
}
