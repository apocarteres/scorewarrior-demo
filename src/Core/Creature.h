
#ifndef CREATURE_H
#define CREATURE_H

#include <iostream>
#include <ostream>
#include <memory>

namespace sw::demo
{
	class Creature
	{
		uint32_t id;
		int hp;
		const int maxHp;
		bool is_remote_attackable;
		bool is_melee_attackable;
		bool is_rigid;
		std::string name;

	public:
		Creature(
			uint32_t id,
			int hp,
			bool is_remote_attackable,
			bool is_melee_attackable,
			bool is_rigid,
			const std::string& name) :
				id(id),
				hp(hp),
				maxHp(hp),
				is_remote_attackable(is_remote_attackable),
				is_melee_attackable(is_melee_attackable),
				is_rigid(is_rigid),
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
