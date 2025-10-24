
#include "Character.h"

#include "Features/Intention/ChangePosition.h"

using namespace sw::demo;

bool Character::turn(uint32_t tick, map::Map* map, const CreaturesContainer& creatures)
{
	for (auto& intention : intentions)
	{
		if (intention->exec(tick, map, creatures))
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

void Character::move(int targetX, int targetY)
{
	if (movePoints < 1)
	{
		return;
	}
	std::erase_if(
		intentions,
		[](const std::unique_ptr<Intention>& ptr) { return dynamic_cast<ChangePosition*>(ptr.get()) != nullptr; });
	intentions.push_back(std::make_unique<ChangePosition>(targetX, targetY, movePoints, creature));
}
