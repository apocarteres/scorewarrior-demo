
#include "RangedAttack.h"

using namespace sw::demo;

bool RangedAttack::exec(uint32_t tick, map::Map* map, const CreaturesContainer& creatures)
{
	if (const auto neighbors = map->lookupNeighbors(creature->getId(), 1); !neighbors.empty())
	{
		return false;
	}

	auto candidateIds = map->lookupNeighbors(creature->getId(), range);
	for (auto& candidateId : candidateIds)
	{
		const auto& target = creatures.at(candidateId);
		auto d = map->distance(creature->getId(), target->getId());
		if (target->getName() == "Raven")
		{
			++d;
		}
		if (d >= MIN_ATTACK_RANGE && d <= range)
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