#include <cmath>
#include <iostream>
#include <iterator>
#include <set>
#include <utility>
#include <vector>

using Point = std::pair<int, int>;

struct PointDistance
{
	Point point;
	unsigned int distance;
};

inline bool operator <(const PointDistance& lhs, const PointDistance& rhs) noexcept
{
	return lhs.distance < rhs.distance;
}

std::ostream& operator <<(std::ostream& outputStream, const Point& point) noexcept
{
	outputStream << "[ " << point.first << ", " << point.second << " ]";

	return outputStream;
}

std::vector<Point> GetClosestPoints(const std::vector<Point>& points, const Point& centralPoint, const unsigned int k) noexcept
{
	std::set<PointDistance> sortedPoints;

	for (const auto& point : points)
	{
		unsigned int currentDistance = std::abs(point.first + centralPoint.first) + std::abs(point.second + centralPoint.second);
		sortedPoints.insert({ point, currentDistance });
	}

	std::vector<Point> closestPoints(k);
	auto sortedPointsIterator = std::cbegin(sortedPoints);

	for (unsigned int i = 0; i < closestPoints.size() && sortedPointsIterator != std::cend(sortedPoints); i++)
	{
		closestPoints[i] = sortedPointsIterator->point;
		sortedPointsIterator++;
	}

	return closestPoints;
}

template <typename T>
void PrintVector(const std::vector<T>& values) noexcept
{
	for (const auto& value : values)
	{
		std::cout << value << " ";
	}

	std::cout << "\n";
}

int main(int argc, char* argv[])
{
	PrintVector(GetClosestPoints({ { 0, 0 }, { 5, 4 }, { 3, 1 } }, { 1, 2 }, 2));

	std::cin.get();

	return 0;
}