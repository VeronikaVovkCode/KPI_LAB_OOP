#include "pch.h"
#include "Pathfinder.h"

bool Pathfinder::Init(const TileContainer& container, uint32_t xpos, uint32_t ypos, uint32_t xgoal, uint32_t ygoal)
{
	m_pathList.clear();
	m_closedList.clear();
	m_path.clear();

	using INT_PAIR = std::pair<int32_t, int32_t>;
	static constexpr INT_PAIR deltas[] = {
		INT_PAIR{ 0, -1}, // NORTH
		INT_PAIR{ 1,  0}, // EAST
		INT_PAIR{ 0,  1}, // SOUTH
		INT_PAIR{-1,  0}, // WEST
	};

	uint32_t w = (uint32_t)container.size();
	ASSERT(w > 0);
	uint32_t h = (uint32_t)container[0].size();
	ASSERT(xpos < w && ypos < h);

	// Resize pathlist
	m_pathList.resize(w);
	for (auto& v : m_pathList)
		v.resize(h);

	// Resize closedlist
	m_closedList.resize(w);
	for (auto& v : m_closedList)
		v.resize(h);

	std::priority_queue<Node, std::vector<Node>, std::greater<Node>> openList;
	Node& start = m_pathList[xpos][ypos];
	start = Node(xpos, ypos, 0.0f, 0.0f); // we dont care about priority here
	openList.push(start);

	while (!openList.empty())
	{
		Node node = openList.top();
		if (node.x == xgoal && node.y == ygoal)
		{
			break;
		}

		// Mark node as closed one (as we just traversed it)
		openList.pop();
		m_closedList[node.x][node.y] = true; // we just traversed the node
		for (uint32_t i = 0; i < 4; ++i)
		{
			auto [dx, dy] = deltas[i];
			uint32_t nx = node.x + dx;
			uint32_t ny = node.y + dy;

			// if coords are out of bounds, than no neighbor there
			if (nx >= w || ny > h || m_closedList[nx][ny])
				continue;

			Tile* neighbor = container[nx][ny];
			if (neighbor->IsCollider())
				continue; // If thats a wall, we cannot traverse there

			float g = m_pathList[node.x][node.y].g + 1;
			float h = this->Heuristic(nx, ny, xgoal, ygoal);
			Node neighborNode(nx, ny, g, h);
			neighborNode.SetParent(node.x, node.y);

			// If we have already traversed the neighbor, then the prio will be > 0
			// We need to either update it or add new
			float f = m_pathList[nx][ny].GetPriority();
			if (f == 0.0f || neighborNode.GetPriority() < f)
			{
				openList.push(neighborNode);
				m_pathList[nx][ny] = neighborNode;
			}
		}
	}

	this->RecreatePath(xgoal, ygoal);
	return true;
}

void Pathfinder::RecreatePath(uint32_t xgoal, uint32_t ygoal)
{
	uint32_t xcurrent = xgoal;
	uint32_t ycurrent = ygoal;

	while (m_pathList[xcurrent][ycurrent].HasParent())
	{
		Node& node = m_pathList[xcurrent][ycurrent];
		m_path.push_back({xcurrent, ycurrent});
		xcurrent = node.px;
		ycurrent = node.py;
	}

	std::reverse(m_path.begin(), m_path.end());

	Node& start = m_pathList[xcurrent][ycurrent];
	m_path.insert(m_path.begin(), { start.x, start.y });
}

float Pathfinder::Heuristic(uint32_t x, uint32_t y, uint32_t goalx, uint32_t goaly)
{
	// Convert to int from uint to avoid crit errors
	uint32_t dx = std::abs((int32_t)x - (int32_t)goalx);
	uint32_t dy = std::abs((int32_t)y - (int32_t)goaly);
	return static_cast<float>(dx + dy);
}
