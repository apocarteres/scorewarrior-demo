
#include "Game.h"

#include "IO/Events/MapCreated.hpp"
#include "IO/Events/MarchStarted.hpp"
#include "IO/Events/UnitSpawned.hpp"

#include <algorithm>

using namespace sw::demo;

void Game::createMap(uint32_t width, uint32_t height)
{
	map = std::make_unique<map::Map>(width, height);
	eventLog.log(tick, io::MapCreated{width, height});
}

void Game::spawn(Character&& character, int x, int y)
{
	uint32_t id = character.getId();
	if (findCharacter(id) != nullptr)
	{
		throw std::runtime_error("Creature already exists");
	}
	if (!map->isAvailable(x, y))
	{
		throw std::runtime_error("Can't spawn here, already occupied");
	}
	eventLog.log(tick, io::UnitSpawned{id, character.creature->getName(), (uint32_t) x, (uint32_t) y});
	map->occupy(id, character.creature->isRigid(), x, y);
	characters.push_back(std::make_shared<Character>(std::move(character)));
}

void Game::march(uint32_t id, int targetX, int targetY)
{
	auto character = findCharacter(id);
	if (character == nullptr)
	{
		throw std::runtime_error("Creature not found");
	}
	auto xy = map->lookupObject(id);
	if (character->move(targetX, targetY))
	{
		eventLog.log(tick, io::MarchStarted{id, (uint32_t) xy.x, (uint32_t) xy.y, (uint32_t) targetX, (uint32_t) targetY});
	}
}

CharacterPtr Game::findCharacter(uint32_t id) const
{
	for (auto& character : characters)
	{
		if (character->getId() == id)
		{
			return character;
		}
	}
	return nullptr;
}

void Game::removeDeadCreatures()
{
	for (auto it = characters.cbegin(); it != characters.cend();)
	{
		auto creature = (*it)->creature;
		if (creature->getHp() == 0)
		{
			map->release(creature->getId());
			it = characters.erase(it);
		}
		else
		{
			++it;
		}
	}
}

bool Game::turn()
{
	++tick;
	removeDeadCreatures();
	if (characters.size() <= 1)
	{
		return false;
	}
	bool playable = false;
	CreaturesContainer creatures;
	for (auto& character : characters)
	{
		creatures.emplace(character->getId(), character->creature);
	}
	for (auto& character : characters)
	{
		playable |= character->turn(tick, map.get(), creatures);
	}
	return playable;
}

uint32_t Game::getTick() const
{
	return tick;
}

void Game::debug() const
{
	map->print();
	for (auto& character : characters)
	{
		std::cout << "Unit " << character->getId() << " HP: " << character->creature->getHp() << std::endl;
	}
}


int Game::getHpOf(uint32_t id) const
{
	auto charPtr = findCharacter(id);
	if (charPtr == nullptr)
	{
		throw std::runtime_error("Creature not found");
	}
	return charPtr->creature->getHp();
}
