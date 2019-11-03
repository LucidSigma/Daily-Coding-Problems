#include <cmath>
#include <cstddef>
#include <cstdlib>
#include <iostream>
#include <limits>
#include <stdexcept>
#include <utility>
#include <vector>

using Point = std::pair<int, int>;

std::pair<Point, Point> GetClosestPoints(const std::vector<Point>& points)
{
	if (points.size() <= 1)
	{
		throw std::invalid_argument("Not enough points passed.");
	}

	unsigned int minDistance = std::numeric_limits<unsigned int>::max();
	std::pair<Point, Point> closestPoints;

	for (size_t i = 0; i < points.size() - 1; ++i)
	{
		for (size_t j = i + 1; j < points.size(); ++j)
		{
			const auto [x1, y1] = points[i];
			const auto [x2, y2] = points[j];

			const unsigned int currentDistance = static_cast<unsigned int>(std::sqrt(std::pow(x1 - x2, 2) + std::pow(y1 - y2, 2)));

			if (currentDistance < minDistance)
			{
				minDistance = currentDistance;
				closestPoints = { points[i], points[j] };
			}
		}
	}

	return closestPoints;
}

template <typename T, typename U>
inline std::ostream& operator <<(std::ostream& outputStream, const std::pair<T, U>& pair)
{
	outputStream << "( " << pair.first << ", " << pair.second << " )";

	return outputStream;
}

int main(const int argc, const char* const argv[])
{
	const std::vector<Point> points
	{
		{ 1, 1 },
		{ -1, -1 },
		{ 3, 4 },
		{ 6, 1 },
		{ -1, -6 },
		{ -4, -3 }
	};

	std::cout << GetClosestPoints(points) << "\n";

	std::cin.get();

	return EXIT_SUCCESS;
}