
#include "Cell.h"

void sw::demo::map::Cell::addBody(uint32_t body)
{
	bodies.insert(body);
}

void sw::demo::map::Cell::addShadow(uint32_t shadow)
{
	shadows.insert(shadow);
}

bool sw::demo::map::Cell::hasBodies()
{
	return !bodies.empty();
}

bool sw::demo::map::Cell::containsBody(uint32_t id)
{
	return bodies.find(id) != bodies.end();
}

bool sw::demo::map::Cell::containsShadow(uint32_t id)
{
	return shadows.find(id) != shadows.end();
}

void sw::demo::map::Cell::dropBody(uint32_t id)
{
	bodies.erase(id);
}

void sw::demo::map::Cell::dropShadow(uint32_t id)
{
	shadows.erase(id);
}

std::vector<uint32_t> sw::demo::map::Cell::getShadows()
{
	std::vector<uint32_t> occupants;
	for (auto& id : shadows)
	{
		occupants.push_back(id);
	}
	return occupants;
}

std::vector<uint32_t> sw::demo::map::Cell::getBodies()
{
	std::vector<uint32_t> occupants;
	for (auto& id : bodies)
	{
		occupants.push_back(id);
	}
	return occupants;
}

std::vector<uint32_t> sw::demo::map::Cell::getAll()
{
	std::vector<uint32_t> occupants;
	for (auto& id : shadows)
	{
		occupants.push_back(id);
	}
	for (auto& id : bodies)
	{
		occupants.push_back(id);
	}
	return occupants;
}

void sw::demo::map::Cell::clear()
{
	bodies.clear();
	shadows.clear();
}
