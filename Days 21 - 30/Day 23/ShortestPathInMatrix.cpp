#include <iostream>
#include <queue>
#include <vector>

struct Point
{
	int x;
	int y;

	bool operator ==(const Point& other) const
	{
		return ((x == other.x) && (y == other.y));
	}
};

struct Node
{
	Point point;
	int distance;
};

inline bool IsInMatrix(unsigned int row, unsigned int column, unsigned int rowCount, unsigned int columnCount) noexcept
{
	return ((row < rowCount) && (column < columnCount));
}

int GetStepCount(const std::vector<std::vector<bool>>& matrix, Point start, Point end)
{
	constexpr int INVALID_PATH = -1;

	if (matrix[start.x][start.y] || matrix[end.x][end.y])
	{
		return INVALID_PATH;
	}

	std::vector<std::vector<bool>> visitedPoints(matrix.size(), std::vector<bool>(matrix[0].size(), false));
	visitedPoints[start.x][start.y] = true;

	std::queue<Node> nodes;

	Node startNode { start, 0 };
	nodes.push(startNode);

	while (!nodes.empty())
	{
		Node currentNode = nodes.front();
		Point currentPoint = currentNode.point;

		if (currentPoint == end)
		{
			return currentNode.distance;
		}

		nodes.pop();

		constexpr unsigned int SURROUNDING_NODES = 4;
		constexpr int ROW_RELATIONS[SURROUNDING_NODES] { -1, 0, 0, 1 };
		constexpr int COLUMN_RELATIONS[SURROUNDING_NODES] { 0, -1, 1, 0 };

		for (unsigned int i = 0; i < SURROUNDING_NODES; i++)
		{
			int currentRow = currentPoint.x + ROW_RELATIONS[i];
			int currentColumn = currentPoint.y + COLUMN_RELATIONS[i];

			if (IsInMatrix(currentRow, currentColumn, matrix.size(), matrix[0].size()) && !matrix[currentRow][currentColumn] && !visitedPoints[currentRow][currentColumn])
			{
				visitedPoints[currentRow][currentColumn] = true;

				Point targetPoint { currentRow, currentColumn };
				Node targetNode { targetPoint, currentNode.distance + 1 };

				nodes.push(targetNode);
			}
		}
	}

	return INVALID_PATH;
}

int main(int argc, const char* argv[])
{
	std::vector<std::vector<bool>> matrix
	{
		{ false, false, false, false },
		{  true,  true, false,  true },
		{ false, false, false, false },
		{ false, false, false, false }
	};

	Point start { 3, 0 };
	Point end { 0, 0 };

	std::cout << GetStepCount(matrix, start, end) << std::endl;

	std::cin.get();

	return 0;
}