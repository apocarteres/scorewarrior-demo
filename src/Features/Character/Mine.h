
#ifndef MINE_H
#define MINE_H
#include <Core/Character.h>
#include <Features/Intention/Explosion.h>

#define MINE_ACTIVATION_RANGE (2)
#define MINE_DAMAGE_RANGE (3)

namespace sw::demo
{
	class Mine final : public Character
	{
	public:
		Mine(uint32_t id, uint32_t power) :
				Character(Creature{id, 1, false, false, false, "Mine"}, 0)
		{
			intentions.push_back(
				std::make_unique<Explosion>(power, MINE_ACTIVATION_RANGE, MINE_DAMAGE_RANGE, creature));
		}
	};
}

#endif	//MINE_H
