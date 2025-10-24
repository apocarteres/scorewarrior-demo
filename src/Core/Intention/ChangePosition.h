
#ifndef CHANGEPOSITION_H
#define CHANGEPOSITION_H
#include "Intention.h"

namespace sw::demo
{
	class ChangePosition : public Intention
	{
		int targetX;
		int targetY;
		int movePoints;

	public:
		ChangePosition(int targetX, int targetY, int movePoints, const CreaturePtr& creature) :
				Intention(creature),
				targetX(targetX),
				targetY(targetY),
				movePoints(movePoints)
		{}

		bool exec(Map* map, std::unordered_map<uint32_t, CreaturePtr> creatures) override;
	};
}

#endif	//CHANGEPOSITION_H
