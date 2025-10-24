
#include "Explosion.h"

using namespace sw::demo;

bool Explosion::exec(Map* map, std::unordered_map<uint32_t, CreaturePtr> creatures)
{
	if (armed)
	{
		auto candidateIds = map->lookupNeighbors(creature->getId(), damageRange);
		for (auto& candidateId : candidateIds)
		{
			auto candidate = creatures[candidateId];
			candidate->takeDamage(power);
		}
		creature->takeDamage(1);
		std::cout<< "Mine " << creature->getId() << " exploded!" << std::endl;
		return true;
	}
	auto candidateIds = map->lookupNeighbors(creature->getId(), activationRange);
	if (candidateIds.empty())
	{
		return false;
	}
	std::cout<< "Mine " << creature->getId() << " gets armed!" << std::endl;
	armed = true;
	return true;
}