
#ifndef CHARACTER_H
#define CHARACTER_H

#include "Core/Intention/Intention.h"

namespace sw::demo
{
	class Character
	{
	protected:
		uint32_t movePoints;
		std::vector<IntentionPtr> intentions;

		Character(Creature&& creature, uint32_t movePoints) : movePoints(movePoints)
		{
			this->creature = std::make_shared<Creature>(std::move(creature));
		}

	public:
		CreaturePtr creature;

		bool turn(uint32_t tick, map::Map* map, const CreaturesContainer& creatures);

		[[nodiscard]]
		uint32_t getId() const;

		void move(int targetX, int targetY);
	};

	typedef std::shared_ptr<Character> CharacterPtr;
}

#endif	//CHARACTER_H
