
#include "Game.h"

void Game::createMap(uint32_t width, uint32_t height)
{
	map = std::make_unique<Map>(width, height);
	std::cout << "New map " << width << "x" << height << " has been created" << std::endl;
}

void Game::spawn(Character&& character, int x, int y)
{
	uint32_t id = character.getId();
	if (characters.contains(id))
	{
		throw std::runtime_error("Creature already exists");
	}
	if (!map->isAvailable(x, y))
	{
		throw std::runtime_error("Can't spawn here, already occupied");
	}
	map->occupy(id, character.creature->isRigid(), x, y);
	characters.emplace(id, std::make_unique<Character>(std::move(character)));
}

void Game::removeDeadCreatures()
{
	for (auto it = characters.cbegin(); it != characters.cend();)
	{
		auto creature = it->second->creature;
		if (creature->getHp() == 0)
		{
			map->release(creature->getId());
			characters.erase(it++);
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
	for (auto& [id, character] : characters)
	{
		creatures.emplace(id, character->creature);
	}
	for (auto& [id, character] : characters)
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
}

void Game::march(uint32_t id, int target_x, int target_y)
{
	characters[id]->move(target_x, target_y);
}
