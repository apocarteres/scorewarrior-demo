
#ifndef MELEEATTACK_H
#define MELEEATTACK_H
#include "Intention.h"

class MeleeAttack : public Intention{
	int power;

public:
	MeleeAttack(int power, const CreaturePtr& creature) :
			Intention(creature), power(power){}

	bool exec(Map* map, std::unordered_map<uint32_t, CreaturePtr> creatures) override;
};



#endif //MELEEATTACK_H
