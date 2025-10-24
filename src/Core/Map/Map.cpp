#include "Core/Map/Map.h"

#include <cmath>

using namespace sw::demo::map;

void Map::cleanup()
{
	for (uint32_t i = 0; i < width * height; ++i)
	{
		field[i].clear();
	}
}

bool Map::occupy(uint32_t id, bool rigid, int x, int y)
{
	if (!isValid(x, y))
	{
		return false;
	}
	Cell& cell = field[y * width + x];
	if (rigid)
	{
		if (isAvailable(x, y))
		{
			cell.addBody(id);
		}
		else
		{
			return false;
		}
	}
	else
	{
		cell.addShadow(id);
	}
	return true;
}

bool Map::isAvailable(int x, int y) const
{
	if (!isValid(x, y))
	{
		return false;
	}
	return !field[y * width + x].hasBodies();
}

bool Map::move(uint32_t id, int dst_x, int dst_y, int step)
{
	auto object = lookupObject(id);
	if (!isValid(object.x, object.y))
	{
		return false;
	}
	auto src_x = object.x;
	auto src_y = object.y;
	if (src_x > dst_x)
	{
		src_x -= step;
	}
	else if (src_x < dst_x)
	{
		src_x += step;
	}
	if (src_y > dst_y)
	{
		src_y -= step;
	}
	else if (src_y < dst_y)
	{
		src_y += step;
	}
	if (src_x >= width)
	{
		src_x = width - 1;
	}
	if (src_x < 0)
	{
		src_x = 0;
	}
	if (src_y >= height)
	{
		src_y = height - 1;
	}
	if (src_y < 0)
	{
		src_y = 0;
	}
	bool move_required = (src_x != object.x) || (src_y != object.y);
	bool available = (!object.rigid) || (isAvailable(src_x, src_y));
	if (move_required && available)
	{
		release(id);
		occupy(id, object.rigid, src_x, src_y);
		return true;
	}
	return false;
}

Object Map::lookupObject(uint32_t id) const
{
	for (int i = 0; i < width * height; ++i)
	{
		auto y = i / width;
		auto x = i - y * width;
		Cell& cell = field[y * width + x];
		if (cell.containsShadow(id))
		{
			return {x, y, false};
		}
		if (cell.containsBody(id))
		{
			return {x, y, true};
		}
	}
	return {-1, -1, false};
}

std::vector<uint32_t> Map::lookupNeighbors(uint32_t id, int level) const
{
	auto object = lookupObject(id);
	if (!isValid(object.x, object.y))
	{
		return {};
	}
	return lookupNeighbors(object.x, object.y, level);
}

std::vector<uint32_t> Map::lookupNeighbors(int x, int y, int level) const
{
	std::vector<uint32_t> occupants;
	for (int row = -level; row <= level; ++row)
	{
		for (int col = -level; col <= level; ++col)
		{
			if (row == 0 && col == 0)
			{
				continue;
			}
			auto lx = x + col;
			auto ly = y + row;
			if (!isValid(lx, ly))
			{
				continue;
			}
			Cell& cell = field[ly * width + lx];
			for (auto& id : cell.getAll())
			{
				occupants.push_back(id);
			}
		}
	}
	return occupants;
}

void Map::print() const
{
	int j = 0;
	for (int i = 0; i < width * height; ++i)
	{
		Cell& cell = field[i];
		auto totalOccupants = cell.getAll();
		if (totalOccupants.size() > 1)
		{
			std::cout << " * ";
		}
		else if (totalOccupants.size() == 1)
		{
			auto bodies = cell.getBodies();
			auto shadows = cell.getShadows();
			if (bodies.empty())
			{
				std::cout << "*" << shadows[0] << " ";
			}
			else
			{
				std::cout << " " << bodies[0] << " ";
			}
		} else
		{
			std::cout << " . ";
		}
		if (++j == width)
		{
			j = 0;
			std::cout << std::endl;
		}
	}
}

bool Map::isValid(std::pair<int, int> xy) const
{
	return isValid(xy.first, xy.second);
}

bool Map::isValid(int x, int y) const
{
	if (x < 0 || y < 0 || x >= width || y >= height)
	{
		return false;
	}
	return true;
}

void Map::release(uint32_t id)
{
	auto object = lookupObject(id);
	if (!isValid(object.x, object.y))
	{
		return;
	}
	Cell& cell = field[object.y * width + object.x];
	cell.dropBody(id);
	cell.dropShadow(id);
}

int Map::distance(uint32_t src_id, uint32_t dst_id) const
{
	auto src_point = lookupObject(src_id);
	auto dst_point = lookupObject(dst_id);
	int mod_x = static_cast<int>(std::floor(std::pow(std::abs(dst_point.x - src_point.x), 2)));
	int mod_y = static_cast<int>(std::floor(std::pow(std::abs(dst_point.y - src_point.y), 2)));
	return static_cast<int>(std::floor(std::sqrt(mod_y + mod_x)));
}
