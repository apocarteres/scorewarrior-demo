
#ifndef RAVEN_H
#define RAVEN_H
#include <Core/Character.h>
#include <Features/Intention/MeleeAttack.h>

namespace sw::demo
{
	class Raven final : public Character
	{
	public:
		Raven(uint32_t id, uint32_t hp, uint32_t agility) :
				Character(Creature{id, hp, true, false, false, "Raven"}, 2)
		{
			intentions.push_back(std::make_unique<MeleeAttack>(agility, creature));
		}
	};
}

#endif	//RAVEN_H
