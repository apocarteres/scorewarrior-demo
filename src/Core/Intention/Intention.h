
#ifndef INTENTION_H
#define INTENTION_H

#include "Core/Creature.h"
#include "Core/Map.h"

#include <ostream>
#include <utility>
#include <unordered_map>

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

		virtual bool exec(Map* map, std::unordered_map<uint32_t, CreaturePtr> creatures) = 0;
	};

	typedef std::unique_ptr<Intention> IntentionPtr;
}
#endif	//INTENTION_H
