#include "Core/Creature.h"
#include "Core/Game.h"
#include "Features/Creatures/Healer.h"
#include "Features/Creatures/Hunter.h"
#include "Features/Creatures/Swordsman.h"
#include "Features/Creatures/Tower.h"
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

	using namespace demo;

	Game game;
	io::CommandParser parser;
	parser
		.add<io::CreateMap>(
			[&game](auto command)
			{
				game.createMap(command.width, command.height);
				printDebug(std::cout, command);
			})
		.add<io::SpawnSwordsman>(
			[&game](auto command)
			{
				game.spawn(Swordsman{command.unitId, command.hp, command.strength}, (int)command.x, (int)command.y);
				printDebug(std::cout, command);
			})
		.add<io::SpawnHunter>(
			[&game](auto command)
			{
				game.spawn(
					Hunter{command.unitId, command.hp, command.strength, command.range, command.agility},
					(int)command.x,
					(int)command.y);
				printDebug(std::cout, command);
			})
		.add<io::March>(
			[&game](auto command)
			{
				game.march(command.unitId, (int)command.targetX, (int)command.targetY);
				printDebug(std::cout, command);
			});

	parser.parse(file);
	std::cout << "Game started" << std::endl;
	game.debug();
	while (game.turn())
	{
		std::cout << "Turn " << game.getTick() << "\n";
		game.debug();
	}
	game.debug();
	std::cout << "Game finished" << std::endl;

	return 0;
}
