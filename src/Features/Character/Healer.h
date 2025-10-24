
#ifndef HEALER_H
#define HEALER_H
#include "../../Core/Character.h"
#include "../Intention/HpRestore.h"

namespace sw::demo
{
	class Healer final : public Character
	{
	public:
		Healer(uint32_t id, uint32_t hp, uint32_t spirit) :
				Character(Creature{id, hp, true, true, true, "Healer"}, 1)
		{
			intentions.push_back(std::make_unique<HpRestore>(spirit, 2, creature));
		}
	};
}

#endif	//HEALER_H
