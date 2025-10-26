
#include "ChangePosition.h"

#include "IO/Events/UnitMoved.hpp"

using namespace sw::demo;

bool ChangePosition::exec(uint32_t tick, map::Map* map, const CreaturesContainer& creatures)
{
	if (creature->getHp() == 0)
	{
		return false;
	}
	auto id = creature->getId();
	auto moved = map->move(creature->getId(), targetX, targetY, movePoints);
	if (moved)
	{
		auto dst = map->lookupObject(id);
		eventLog.log(tick, io::UnitMoved{creature->getId(), (uint32_t) dst.x, (uint32_t) dst.y});
	}
	return moved;
}
