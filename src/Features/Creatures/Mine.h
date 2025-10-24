
#ifndef MINE_H
#define MINE_H
#include "Character.h"
#include "Core/Intention/Explosion.h"

#define MINE_ACTIVATION_RANGE (2)
#define MINE_DAMAGE_RANGE (3)

namespace sw::demo
{
	class Mine : public Character
	{
	public:
		Mine(uint32_t id, uint32_t power) :
				Character(id, "Mine", 1, false, 0, false, false)
		{
			intentions.push_back(
				std::make_unique<Explosion>(power, MINE_ACTIVATION_RANGE, MINE_DAMAGE_RANGE, creature));
		}
	};
}

#endif	//MINE_H
