
#ifndef INTENTION_H
#define INTENTION_H

#include "Core/Map/Map.h"
#include "Core/Creature.h"
#include "IO/Events/UnitAttacked.hpp"
#include "IO/Events/UnitDied.hpp"
#include "IO/System/EventLog.hpp"

#include <ostream>
#include <unordered_map>
#include <utility>

namespace sw::demo
{
	class Intention
	{
	protected:
		CreaturePtr creature;
		EventLog eventLog;


		void logDamageDealt(uint32_t tick, const CreaturePtr& attacker, const CreaturePtr& target, uint32_t damage)
		{
			auto hp = (uint32_t) target->getHp();
			eventLog.log(tick, io::UnitAttacked{attacker->getId(), target->getId(), damage, hp});
			if (hp == 0)
			{
				eventLog.log(tick, io::UnitDied{target->getId()});
			}

		}

	public:
		explicit Intention(CreaturePtr creature) :
				creature(std::move(creature))
		{}

		virtual ~Intention() = default;

		virtual bool exec(uint32_t tick, map::Map* map, CreaturesContainer creatures) = 0;
	};

	typedef std::unique_ptr<Intention> IntentionPtr;
}
#endif	//INTENTION_H
