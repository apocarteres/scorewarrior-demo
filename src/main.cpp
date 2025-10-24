#include "Core/Creature.h"
#include "Core/Game.h"
#include "Features/Creatures/Healer.h"
#include "Features/Creatures/Hunter.h"
#include "Features/Creatures/Swordsman.h"
#include "IO/System/TypeRegistry.hpp"

#include <IO/Commands/CreateMap.hpp>
#include <IO/Commands/March.hpp>
#include <IO/Commands/SpawnHunter.hpp>
#include <IO/Commands/SpawnSwordsman.hpp>
#include <IO/Events/MapCreated.hpp>
#include <IO/Events/MarchEnded.hpp>
#include <IO/Events/MarchStarted.hpp>
#include <IO/Events/UnitAttacked.hpp>
#include <IO/Events/UnitDied.hpp>
#include <IO/Events/UnitMoved.hpp>
#include <IO/Events/UnitSpawned.hpp>
#include <IO/System/CommandParser.hpp>
#include <IO/System/EventLog.hpp>
#include <IO/System/PrintDebug.hpp>
#include <fstream>
#include <iostream>

void runUnitTests();

int main(int argc, char** argv)
{
	runUnitTests();

	using namespace sw;

	if (argc != 2)
	{
		throw std::runtime_error("Error: No file specified in command line argument");
	}

	std::ifstream file(argv[1]);
	if (!file)
	{
		throw std::runtime_error("Error: File not found - " + std::string(argv[1]));
	}

	Game game;
	game.createMap(10, 10);
	game.spawn(Swordsman{1, 10, 5}, 5, 5);
	game.spawn(Swordsman{2, 10, 5}, 1, 8);
	game.spawn(Hunter{3, 10, 2, 5, 3}, 2, 2);
	game.spawn(Healer{4, 10, 2}, 5, 7);
	game.march(4, 0,0 );

	std::cout << "Game started" << std::endl;
	game.debug();
	while (game.turn())
	{
		std::cout << "Turn " << game.getTick() << "\n";
		game.debug();
	}
	game.debug();
	std::cout << "Game finished" << std::endl;

	exit(0);

	// Code for example...

	std::cout << "Commands:\n";
	io::CommandParser parser;
	parser.add<io::CreateMap>([](auto command) { printDebug(std::cout, command); })
		.add<io::SpawnSwordsman>([](auto command) { printDebug(std::cout, command); })
		.add<io::SpawnHunter>([](auto command) { printDebug(std::cout, command); })
		.add<io::March>([](auto command) { printDebug(std::cout, command); });

	parser.parse(file);

	std::cout << "\n\nEvents:\n";

	EventLog eventLog;

	eventLog.log(1, io::MapCreated{10, 10});
	eventLog.log(1, io::UnitSpawned{1, "Swordsman", 0, 0});
	eventLog.log(1, io::UnitSpawned{2, "Hunter", 9, 0});
	eventLog.log(1, io::MarchStarted{1, 0, 0, 9, 0});
	eventLog.log(1, io::MarchStarted{2, 9, 0, 0, 0});
	eventLog.log(1, io::UnitSpawned{3, "Swordsman", 0, 9});
	eventLog.log(1, io::MarchStarted{3, 0, 9, 0, 0});

	eventLog.log(2, io::UnitMoved{1, 1, 0});
	eventLog.log(2, io::UnitMoved{2, 8, 0});
	eventLog.log(2, io::UnitMoved{3, 0, 8});

	eventLog.log(3, io::UnitMoved{1, 2, 0});
	eventLog.log(3, io::UnitMoved{2, 7, 0});
	eventLog.log(3, io::UnitMoved{3, 0, 7});

	eventLog.log(4, io::UnitMoved{1, 3, 0});
	eventLog.log(4, io::UnitAttacked{2, 1, 5, 0});
	eventLog.log(4, io::UnitDied{1});
	eventLog.log(4, io::UnitMoved{3, 0, 6});

	eventLog.log(5, io::UnitMoved{2, 6, 0});
	eventLog.log(5, io::UnitMoved{3, 0, 5});

	eventLog.log(6, io::UnitMoved{2, 5, 0});
	eventLog.log(6, io::UnitMoved{3, 0, 4});

	eventLog.log(7, io::UnitAttacked{2, 3, 5, 5});
	eventLog.log(7, io::UnitMoved{3, 0, 3});

	eventLog.log(8, io::UnitAttacked{2, 3, 5, 0});
	eventLog.log(8, io::UnitDied{3});

	// TypeRegistry usage example
	class Dog
	{
	public:
		Dog(std::string name) :
				_name(std::move(name))
		{}

		void makeSound()
		{
			std::cout << _name << " says: Woof!\n";
		}

	private:
		std::string _name;
	};

	TypeRegistry registry;
	registry.emplace<Dog>("Buddy");

	if (auto dog = registry.get<Dog>())
	{
		dog->makeSound();
	}

	return 0;
}
