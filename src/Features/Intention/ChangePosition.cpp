
#include "ChangePosition.h"

using namespace sw::demo;

bool ChangePosition::exec(map::Map* map, std::unordered_map<uint32_t, CreaturePtr> creatures)
{
	std::cout << "Unit " << creature->getId() << " is moving towards [" << targetX << "," << targetY <<"]" << std::endl;
	return map->move(creature->getId(), targetX, targetY, movePoints);
}
