
#ifndef HPRESTORE_H
#define HPRESTORE_H
#include "Core/Intention/Intention.h"

namespace sw::demo
{
	class HpRestore : public Intention
	{
		int spirit;
		int range;

	public:
		HpRestore(int spirit, int range, const CreaturePtr& creature) :
				Intention(creature),
				spirit(spirit),
				range(range)
		{}

		bool exec(Map* map, std::unordered_map<uint32_t, CreaturePtr> creatures) override;
	};
}
#endif //HPRESTORE_H
