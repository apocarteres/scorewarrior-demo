
#include "MeleeAttack.h"

using namespace sw::demo;

bool MeleeAttack::exec(Map* map, std::unordered_map<uint32_t, CreaturePtr> creatures)
{
	auto neighborIds = map->lookupNeighbors(creature->getId(), 1);
	for (auto& neighborId : neighborIds)
	{
		auto neighbor = creatures[neighborId];
		if (neighbor->isMeleeAttackable())
		{
			neighbor->takeDamage(power);
			std::cout << "Applied melee attack from " << creature->getName() << " to " << neighbor->getId() << std::endl;
			return true;
		}
		std::cout << "Melee attack from " << creature->getName() << " is not applicable to " << neighbor->getId() << std::endl;
	}
	std::cout << "No eligible units for melee attack for " << creature->getName() << std::endl;
	return false;
}
