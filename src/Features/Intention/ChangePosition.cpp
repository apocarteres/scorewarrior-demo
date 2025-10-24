
#include "ChangePosition.h"

using namespace sw::demo;

bool ChangePosition::exec(Map* map, std::unordered_map<uint32_t, CreaturePtr> creatures)
{
	if (targetX == -1 && targetY == -1)
	{
		return false;
	}
	std::cout << "Change Position from " << creature->getName() << std::endl;
	return map->move(creature->getId(), targetX, targetY, movePoints);
}
