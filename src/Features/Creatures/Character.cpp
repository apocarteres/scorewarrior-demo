
#include "Character.h"

using namespace sw::demo;

bool Character::turn(Map* map, const std::unordered_map<uint32_t, CreaturePtr>& creatures)
{
	for (auto& intention : intentions)
	{
		if (intention->exec(map, creatures))
		{
			return true;
		}
	}
	return false;
}

uint32_t Character::getId() const
{
	return creature->getId();
}

void Character::move(int target_x, int target_y)
{
	if (movePoints < 1)
	{
		std::cout << "Unit "<< creature->getId() << " is unable to move" << std::endl;
		return;
	}
	std::erase_if(
		intentions,
		[](const std::unique_ptr<Intention>& ptr) { return dynamic_cast<ChangePosition*>(ptr.get()) != nullptr; });
	intentions.push_back(std::make_unique<ChangePosition>(target_x, target_y, movePoints, creature));
}
