
#ifndef CHANGEPOSITION_H
#define CHANGEPOSITION_H
#include "Intention.h"

class ChangePosition : public Intention
{
	int targetX;
	int targetY;

public:
	ChangePosition(int targetX, int targetY, const CreaturePtr& creature) :
			Intention(creature),
			targetX(targetX),
			targetY(targetY)
	{}

	bool exec(Map* map, std::unordered_map<uint32_t, CreaturePtr> creatures) override;
};

#endif	//CHANGEPOSITION_H
