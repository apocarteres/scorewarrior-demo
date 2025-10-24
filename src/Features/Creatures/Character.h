
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

	bool turn(Map* map, const std::unordered_map<uint32_t, CreaturePtr>& creatures);

	[[nodiscard]]
	uint32_t getId() const;

	void move(int target_x, int target_y);
};

typedef std::unique_ptr<Character> CharacterPtr;

#endif	//CHARACTER_H
