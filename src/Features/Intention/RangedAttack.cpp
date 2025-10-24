
#include "RangedAttack.h"

using namespace sw::demo;

bool RangedAttack::exec(uint32_t tick, map::Map* map, CreaturesContainer creatures)
{
	if (const auto neighbors = map->lookupNeighbors(creature->getId(), 1); !neighbors.empty())
	{
		return false;
	}

	auto candidateIds = map->lookupNeighbors(creature->getId(), range);
	for (auto& candidateId : candidateIds)
	{
		auto target = creatures[candidateId];
		auto d = map->distance(creature->getId(), target->getId());
		if (target->getName() == "Raven")
		{
			++d;
		}
		if (d >= 1 && d <= range)
		{
			if (target->takeDamage(power))
			{
				logDamageDealt(tick, creature, target, power);
				return true;
			}
		}
	}
	return false;
}