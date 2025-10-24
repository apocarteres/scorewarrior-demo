
#include "RangedAttack.h"

bool RangedAttack::exec(Map* map, std::unordered_map<uint32_t, CreaturePtr> creatures)
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
		if (d > 1 && d <= range)
		{
			target->takeDamage(agility);
			std::cout << "Hunter " << creature->getId() << " remotely attacked " << target->getId() << std::endl;
			return true;
		}
	}
	std::cout << "Hunter " << creature->getId() << " has no eligible units for remote attack" << std::endl;
	return false;
}