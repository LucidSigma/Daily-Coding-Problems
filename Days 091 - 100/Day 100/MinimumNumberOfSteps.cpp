#include <algorithm>
#include <cmath>
#include <iostream>
#include <vector>

struct Point
{
	int x;
	int y;
};

unsigned int GetMininumNumberOfSteps(const std::vector<Point>& points) noexcept
{
	unsigned int stepCount = 0;

	int previousX = 0;
	int previousY = 0;

	for (const Point& currentPoint : points)
	{
		const unsigned int xDifference = std::abs(currentPoint.x - previousX);
		const unsigned int yDifference = std::abs(currentPoint.y - previousY);

		stepCount += std::max(xDifference, yDifference);

		previousX = currentPoint.x;
		previousY = currentPoint.y;
	}

	return stepCount;
}

int main(int argc, char* argv[])
{
	std::cout << GetMininumNumberOfSteps({ { 0, 0 }, { 1, 1 }, { 1, 2 } }) << "\n";

	std::cin.get();

	return 0;
}