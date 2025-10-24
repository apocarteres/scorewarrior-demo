
#include "HpRestore.h"

using namespace sw::demo;

bool HpRestore::exec(uint32_t tick, map::Map* map, CreaturesContainer creatures)
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
			return true;
		}
	}
	return false;
}