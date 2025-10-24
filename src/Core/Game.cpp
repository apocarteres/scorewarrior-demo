
#include "Game.h"
#include <algorithm>

using namespace sw::demo;

void Game::createMap(uint32_t width, uint32_t height)
{
	map = std::make_unique<map::Map>(width, height);
	std::cout << "New map " << width << "x" << height << " has been created" << std::endl;
}

CharacterPtr Game::findCharacter(uint32_t id)
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
	map->occupy(id, character.creature->isRigid(), x, y);
	characters.push_back(std::make_shared<Character>(std::move(character)));
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
	removeDeadCreatures();
	if (characters.size() <= 1)
	{
		return false;
	}
	bool playable = false;
	std::unordered_map<uint32_t, CreaturePtr> creatures;
	for (auto& character : characters)
	{
		creatures.emplace(character->getId(), character->creature);
	}
	for (auto& character : characters)
	{
		playable |= character->turn(map.get(), creatures);
	}
	++tick;
	return playable;
}

uint32_t Game::getTick() const
{
	return tick;
}

void Game::debug()
{
	map->print();
	for (auto& character : characters)
	{
		std::cout << "Unit " << character->getId() << " HP: " << character->creature->getHp() << std::endl;
	}
}

void Game::march(uint32_t id, int targetX, int targetY)
{
	auto charPtr = findCharacter(id);
	if (charPtr == nullptr)
	{
		throw std::runtime_error("Creature not found");
	}
	charPtr->move(targetX, targetY);
}

int Game::getHpOf(uint32_t id)
{
	auto charPtr = findCharacter(id);
	if (charPtr == nullptr)
	{
		throw std::runtime_error("Creature not found");
	}
	return charPtr->creature->getHp();
}
