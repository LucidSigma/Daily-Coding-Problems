#include <algorithm>
#include <cmath>
#include <iostream>
#include <iterator>
#include <stdexcept>
#include <utility>
#include <vector>

using Point = std::pair<int, int>;

std::ostream& operator <<(std::ostream& outputStream, const Point& point) noexcept
{
	outputStream << "[ " << point.first << ", " << point.second << " ]";

	return outputStream;
}

std::vector<Point> GetClosestPoints(const std::vector<Point>& points, const Point& centralPoint, const unsigned int k)
{
	if (k > points.size())
	{
		throw std::invalid_argument("Point count greater than number of points given.");
	}

	int i = 4;

	std::vector<Point> sortedPoints = points;
	std::sort(std::begin(sortedPoints), std::end(sortedPoints),
		[&centralPoint = std::as_const(centralPoint)](const Point & lhs, const Point & rhs) noexcept -> bool
		{
			unsigned int leftDistance = std::abs(lhs.first + centralPoint.first) + std::abs(lhs.second + centralPoint.second);
			unsigned int rightDistance = std::abs(rhs.first + centralPoint.first) + std::abs(rhs.second + centralPoint.second);
			
			return leftDistance < rightDistance;
		}
	);

	return std::vector<Point>(std::cbegin(sortedPoints), std::cbegin(sortedPoints) + k);
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
