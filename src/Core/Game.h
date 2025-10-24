
#ifndef GAME_H
#define GAME_H

#include "Character.h"
#include "IO/System/EventLog.hpp"

#include <vector>

namespace sw::demo
{
	class Game
	{
		EventLog eventLog;
		std::vector<CharacterPtr> characters;
		std::unique_ptr<map::Map> map;
		uint32_t tick = 1;

		void removeDeadCreatures();
		
		[[nodiscard]]
		CharacterPtr findCharacter(uint32_t id) const;

	public:
		void createMap(uint32_t width, uint32_t height);

		void spawn(Character&& character, int x, int y);

		void march(uint32_t id, int targetX, int targetY);

		bool turn();

		[[nodiscard]]
		uint32_t getTick() const;

		void debug() const;

		[[nodiscard]]
		int getHpOf(uint32_t id) const;
	};
}

#endif	//GAME_H
