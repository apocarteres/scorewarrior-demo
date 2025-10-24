
#ifndef MAP_H
#define MAP_H
#include "Cell.h"
#include "IO/System/EventLog.hpp"

#include <memory>
#include <vector>

namespace sw::demo::map
{
	class Map final
	{
		std::unique_ptr<Cell[]> field;
		EventLog eventLog;

		int width;
		int height;

	public:
		Map(int width, int height) :
				width(width),
				height(height)
		{
			field = std::make_unique<Cell[]>(width * height);
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
		bool isValid(int x, int y) const;

		[[nodiscard]]
		int distance(uint32_t src_id, uint32_t dst_id) const;
	};
}

#endif	//MAP_H
