
#include "HpRestore.h"

using namespace sw::demo;

bool HpRestore::exec(map::Map* map, std::unordered_map<uint32_t, CreaturePtr> creatures)
{
	auto neighborIds = map->lookupNeighbors(creature->getId(), range);
	if (neighborIds.empty())
	{
		return false;
	}
	for (auto& candidateId : neighborIds)
	{
		auto target = creatures[candidateId];
		if (target->restoreHp(spirit))
		{
			std::cout << "Unit " << creature->getId() << " restored " << spirit << " health points for " << target->getId() << std::endl;
			return true;
		}
	}
	std::cout << "Unit " << creature->getId() << " has no eligible targets for restoring HP" << std::endl;
	return false;
}