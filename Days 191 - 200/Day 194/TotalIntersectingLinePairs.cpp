#include <cstdint>
#include <iostream>
#include <utility>
#include <vector>

struct Point
{
	float x;
	float y;
};

using Line = std::pair<Point, Point>;

bool Intersect(const Line& lineA, const Line& lineB) noexcept
{
	const float denominator = ((lineA.second.x - lineA.first.x) * (lineB.second.y - lineB.first.y)) - ((lineA.second.y - lineA.first.y) * (lineB.second.x - lineB.first.x));
	const float firstNumerator = ((lineA.first.y - lineB.first.y) * (lineB.second.x - lineB.first.x)) - ((lineA.first.x - lineB.first.x) * (lineB.second.y - lineB.first.y));
	const float secondNumerator = ((lineA.first.y - lineB.first.y) * (lineA.second.x - lineA.first.x)) - ((lineA.first.x - lineB.first.x) * (lineA.second.y - lineA.first.y));

	if (denominator == 0)
	{
		return firstNumerator == 0 && secondNumerator == 0;
	}

	const float firstResult = firstNumerator / denominator;
	const float secondResult = secondNumerator / denominator;

	return (firstResult >= 0 && firstResult <= 1) && (secondResult >= 0 && secondResult <= 1);
}

unsigned int GetIntersectingPairs(const std::vector<Line>& lines) noexcept
{
	unsigned int intersectionCount = 0;

	for (std::size_t i = 0; i < lines.size() - 1; ++i)
	{
		for (std::size_t j = i + 1; j < lines.size(); ++j)
		{
			if (Intersect(lines[i], lines[j]))
			{
				++intersectionCount;
			}
		}
	}

	return intersectionCount;
}

int main(int argc, char* argv[])
{
	std::cout << GetIntersectingPairs({ { { -4.0f, 1.0f }, { 5.0f, 0.0f } }, { { 1.0f, 0.0f }, { -2.0f, 1.0f } }, { { -3.0f, 1.0f }, { 0.0f, 0.0f } } }) << "\n";

	std::cin.get();

	return 0;
}