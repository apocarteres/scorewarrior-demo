
#ifndef INTENTION_H
#define INTENTION_H

#include "../Map/Map.h"
#include "Core/Creature.h"

#include <ostream>
#include <unordered_map>
#include <utility>

namespace sw::demo
{
	class Intention
	{
	protected:
		CreaturePtr creature;

	public:
		explicit Intention(CreaturePtr creature) :
				creature(std::move(creature))
		{}

		virtual ~Intention() = default;

		virtual bool exec(map::Map* map, std::unordered_map<uint32_t, CreaturePtr> creatures) = 0;
	};

	typedef std::unique_ptr<Intention> IntentionPtr;
}
#endif	//INTENTION_H
