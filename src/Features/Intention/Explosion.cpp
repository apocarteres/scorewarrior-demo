
#include "Explosion.h"

using namespace sw::demo;

bool Explosion::exec(uint32_t tick, map::Map* map, const CreaturesContainer& creatures)
{
	if (armed)
	{
		auto candidateIds = map->lookupNeighbors(creature->getId(), damageRange);
		for (auto& candidateId : candidateIds)
		{
			const auto& candidate = creatures.at(candidateId);
			if (candidate->takeDamage(power))
			{
				logDamageDealt(tick, creature, candidate, power);
			}
		}
		creature->takeDamage(1);
		return true;
	}
	auto candidateIds = map->lookupNeighbors(creature->getId(), activationRange);
	if (candidateIds.empty())
	{
		return false;
	}
	armed = true;
	return true;
}