
#ifndef HEALER_H
#define HEALER_H
#include "../../Core/Character.h"
#include "../Intention/HpRestore.h"

namespace sw::demo
{
	class Healer : public Character
	{
	public:
		Healer(uint32_t id, uint32_t hp, uint32_t spirit) :
				Character(id, "Healer", hp, true, 1, true, true)
		{
			intentions.push_back(std::make_unique<HpRestore>(spirit, 2, creature));
		}
	};
}

#endif	//HEALER_H
