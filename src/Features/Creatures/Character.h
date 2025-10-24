
#ifndef CHARACTER_H
#define CHARACTER_H

#include "Core/Intention/ChangePosition.h"
#include "Core/Intention/Intention.h"

class Character
{
protected:
	std::vector<IntentionPtr> intentions;

	Character(uint32_t id, const std::string& name, uint32_t hp)
	{
		creature = std::make_shared<Creature>(id, hp, true, true, true, name);
	}

public:
	CreaturePtr creature;

	bool turn(Map* map, const std::unordered_map<uint32_t, CreaturePtr>& creatures)
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

	[[nodiscard]]
	uint32_t getId() const
	{
		return creature->getId();
	}

	void move(int target_x, int target_y)
	{
		std::erase_if(
			intentions,
			[](const std::unique_ptr<Intention>& ptr) { return dynamic_cast<ChangePosition*>(ptr.get()) != nullptr; });
		intentions.push_back(std::make_unique<ChangePosition>(target_x, target_y, creature));
	}
};

typedef std::unique_ptr<Character> CharacterPtr;

#endif	//CHARACTER_H
