#include "Core/Creature.h"
#include "Core/Game.h"
#include "Features/Character/Healer.h"
#include "Features/Character/Hunter.h"
#include "Features/Character/Swordsman.h"
#include "Features/Character/Tower.h"
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
	using namespace sw;

	if (argc != 2)
	{
		throw std::runtime_error("Error: No file specified in command line argument");
	}

	if (strcmp(argv[1], "--test") == 0)
	{
		runUnitTests();
		exit(0);
	}

	std::ifstream file(argv[1]);
	if (!file)
	{
		throw std::runtime_error("Error: File not found - " + std::string(argv[1]));
	}

	using namespace demo;

	Game game;
	io::CommandParser parser;
	parser.add<io::CreateMap>([&game](auto command) { game.createMap(command.width, command.height); })
		.add<io::SpawnSwordsman>(
			[&game](auto command)
			{ game.spawn(Swordsman{command.unitId, command.hp, command.strength}, (int)command.x, (int)command.y); })
		.add<io::SpawnHunter>(
			[&game](auto command)
			{
				game.spawn(
					Hunter{command.unitId, command.hp, command.strength, command.range, command.agility},
					(int)command.x,
					(int)command.y);
			})
		.add<io::March>([&game](auto command)
						{ game.march(command.unitId, (int)command.targetX, (int)command.targetY); });

	parser.parse(file);
	while (game.turn())
	{
	}
	return 0;
}
