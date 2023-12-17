#pragma once

#include <vector>
#include <queue>
#include "Tile.h"

class Pathfinder
{
public:
	struct Node
	{
		Node() = default;
		Node(uint32_t x, uint32_t y, float g, float h)
			: x(x)
			, y(y)
			, g(g)
			, h(h)
		{
		}

		inline constexpr bool HasParent() const { return px != uint32_t(-1) && py != uint32_t(-1); }
		inline constexpr void SetParent(uint32_t px, uint32_t py) { this->px = px; this->py = py; }
		inline constexpr float GetPriority() const { return g + h; }

		inline constexpr bool operator>(const Node& other) const { return (g + h) > (other.g + other.h); }

		uint32_t x;
		uint32_t y;
		uint32_t px = uint32_t(-1); // parent
		uint32_t py = uint32_t(-1); // parent
		float g = 0.0f;
		float h = 0.0f;
	};

	using PositionType = std::pair<uint32_t, uint32_t>;
	using TileContainer = std::vector<std::vector<Tile*>>;

	Pathfinder() = default;

	bool Init(const TileContainer& container, uint32_t xpos, uint32_t ypos, uint32_t xgoal, uint32_t ygoal);
	const auto& GetPath() const { return m_path; }

private:
	void RecreatePath(uint32_t xgoal, uint32_t ygoal);
	float Heuristic(uint32_t x, uint32_t y, uint32_t goalx, uint32_t goaly);

	std::vector<PositionType> m_path;
	std::vector<std::vector<Node>> m_pathList;
	std::vector<std::vector<bool>> m_closedList;
};
