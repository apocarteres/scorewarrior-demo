
#ifndef RAVEN_H
#define RAVEN_H
#include "Character.h"
#include "Core/Intention/MeleeAttack.h"

class Raven : public Character
{
public:
	Raven(uint32_t id, uint32_t hp, uint32_t agility) :
			Character(id, "Raven", hp, false, 2, false, true)
	{
		intentions.push_back(std::make_unique<MeleeAttack>(agility, creature));
	}
};



#endif //RAVEN_H
