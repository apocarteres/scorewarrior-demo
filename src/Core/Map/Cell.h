
#ifndef CELL_H
#define CELL_H

#include <set>
#include <vector>

namespace sw::demo::map
{
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

		void addBody(uint32_t body);

		void addShadow(uint32_t shadow);

		bool hasBodies();

		bool containsBody(uint32_t id);

		bool containsShadow(uint32_t id);

		void dropBody(uint32_t id);

		void dropShadow(uint32_t id);

		std::vector<uint32_t> getShadows();

		std::vector<uint32_t> getBodies();

		std::vector<uint32_t> getAll();

		void clear();
	};
}

#endif	//CELL_H
