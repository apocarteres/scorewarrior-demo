
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
		if (target->getName() == "Raven")
		{
			++d;
			std::cout << "Unit " << creature->getId() << " detects Raven " << target->getId() << ", remote attack distance is reduced" << std::endl;
		}
		if (d >= 1 && d <= range)
		{
			target->takeDamage(power);
			std::cout << "Unit " << creature->getId() << " remotely attacked " << target->getId() << std::endl;
			return true;
		}
	}
	std::cout << "Unit " << creature->getId() << " has no eligible targets for remote attack" << std::endl;
	return false;
}