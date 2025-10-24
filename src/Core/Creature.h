
#ifndef CREATURE_H
#define CREATURE_H

#include <iostream>
#include <ostream>
#include <memory>

namespace sw::demo
{
	class Creature final
	{
		uint32_t id;
		uint32_t hp;
		const uint32_t maxHp;
		bool remoteAttackable;
		bool meleeAttackable;
		bool rigid;
		std::string name;

	public:
		Creature(
			uint32_t id,
			uint32_t hp,
			bool remoteAttackable,
			bool meleeAttackable,
			bool rigid,
			const std::string& name) :
				id(id),
				hp(hp),
				maxHp(hp),
				remoteAttackable(remoteAttackable),
				meleeAttackable(meleeAttackable),
				rigid(rigid),
				name(name)
		{
			std::cout << "Creature created: " << name << "[" << id << "]" << std::endl;
		}

		bool takeDamage(int damage);

		bool restoreHp(int spirit);

		[[nodiscard]]
		std::string getName() const;

		[[nodiscard]]
		uint32_t getId() const;

		[[nodiscard]]
		int getHp() const;

		[[nodiscard]]
		bool isRemoteAttackable() const;

		[[nodiscard]]
		bool isMeleeAttackable() const;

		[[nodiscard]]
		bool isRigid() const;
	};

	typedef std::shared_ptr<Creature> CreaturePtr;
}

#endif	//CREATURE_H
