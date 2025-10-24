
#ifndef GAME_H
#define GAME_H

#include "Character.h"

#include <unordered_map>

namespace sw::demo
{
	class Game
	{
		std::unordered_map<uint32_t, CharacterPtr> characters;
		std::unique_ptr<Map> map;
		uint32_t tick = 0;

	protected:
		void removeDeadCreatures();

	public:
		void createMap(uint32_t width, uint32_t height);

		void spawn(Character&& character, int x, int y);

		bool turn();

		[[nodiscard]]
		uint32_t getTick() const;

		void debug();

		void march(uint32_t id, int targetX, int targetY);

		int getHpOf(uint32_t id);
	};
}

#endif	//GAME_H
