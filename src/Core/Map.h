
#ifndef MAP_H
#define MAP_H
#include <iostream>
#include <memory>
#include <set>
#include <vector>

struct Object
{
	int x;
	int y;
	bool rigid;
};

class Cell
{
	std::set<uint32_t> bodies;
	std::set<uint32_t> shadows;
public:
	Cell() = default;
	Cell(const Cell& cell) = delete;
	Cell& operator=(const Cell& cell) = delete;

	void addBody(uint32_t body)
	{
		bodies.insert(body);
	}

	void addShadow(uint32_t shadow)
	{
		shadows.insert(shadow);
	}

	bool hasBodies()
	{
		return !bodies.empty();
	}

	bool containsBody(uint32_t id)
	{
		return bodies.find(id) != bodies.end();
	}

	bool containsShadow(uint32_t id)
	{
		return shadows.find(id) != shadows.end();
	}

	void dropBody(uint32_t id)
	{
		bodies.erase(id);
	}

	void dropShadow(uint32_t id)
	{
		shadows.erase(id);
	}

	std::vector<uint32_t> getShadows()
	{
		std::vector<uint32_t> occupants;
		for (auto& id : shadows)
		{
			occupants.push_back(id);
		}
		return occupants;
	}

	std::vector<uint32_t> getBodies()
	{
		std::vector<uint32_t> occupants;
		for (auto& id : bodies)
		{
			occupants.push_back(id);
		}
		return occupants;
	}

	std::vector<uint32_t> getAll()
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
};

class Map final
{
	std::unique_ptr<std::unique_ptr<Cell>[]> field;

	int width;
	int height;

public:
	Map(int width, int height) :
			width(width),
			height(height)
	{
		field = std::make_unique<std::unique_ptr<Cell>[]>(width * height);
		cleanup();
	}

	void cleanup();

	bool occupy(uint32_t id, bool rigid, int x, int y);

	bool move(uint32_t id, int dst_x, int dst_y, int step);

	void release(uint32_t id);

	void print() const;

	[[nodiscard]]
	bool isAvailable(int x, int y) const;

	[[nodiscard]]
	Object lookupObject(uint32_t id) const;

	[[nodiscard]]
	std::vector<uint32_t> lookupNeighbors(uint32_t id, int level) const;

	[[nodiscard]]
	std::vector<uint32_t> lookupNeighbors(int x, int y, int level) const;

	[[nodiscard]]
	bool isValid(std::pair<int, int> xy) const;

	[[nodiscard]]
	bool isValid(int x, int y) const;

	[[nodiscard]]
	int distance(uint32_t src_id, uint32_t dst_id) const;
};

#endif	//MAP_H
