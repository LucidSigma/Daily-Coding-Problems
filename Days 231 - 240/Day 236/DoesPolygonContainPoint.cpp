#include <algorithm>
#include <array>
#include <cmath>
#include <cstddef>
#include <cstdlib>
#include <iostream>
#include <limits>
#include <tuple>
#include <type_traits>
#include <utility>

struct Point
{
	int x;
	int y;
};

using Line = std::pair<Point, Point>;
using Triangle = std::tuple<Point, Point, Point>;

template <size_t N, typename = std::enable_if_t<(N >= 3)>>
using Polygon = std::array<Point, N>;

enum class Orientation
	: int
{
	Colinear,
	Clockwise,
	Counterclockwise
};

Orientation GetTriangleOrientation(const Triangle& triangle) noexcept
{
	const auto& [a, b, c] = triangle;
	const int sign = (b.y - a.y) * (c.x - b.x) - (b.x - a.x) * (c.y - b.y);

	if (sign == 0)
	{
		return Orientation::Colinear;
	}
	else if (sign > 0)
	{
		return Orientation::Clockwise;
	}
	else
	{
		return Orientation::Counterclockwise;
	}
}

inline bool IsOnLineSegment(const Line& line, const Point& point) noexcept
{
	const auto& [first, second] = line;

	return point.x <= std::max(first.x, second.x) && point.x >= std::min(first.x, second.x) &&
		   point.y <= std::max(first.y, second.y) && point.y >= std::min(first.y, second.y);
}

bool HaveIntersection(const Line& lineA, const Line& lineB) noexcept
{
	const std::array<Orientation, 4> orientations
	{
		GetTriangleOrientation({ lineA.first, lineB.first, lineA.second }),
		GetTriangleOrientation({ lineA.first, lineB.first, lineB.second }),
		GetTriangleOrientation({ lineA.second, lineB.second, lineA.first }),
		GetTriangleOrientation({ lineA.second, lineB.second, lineB.second })
	};

	if (orientations[0] != orientations[1] && orientations[2] != orientations[3])
	{
		return true;
	}

	if (orientations[0] == Orientation::Colinear && IsOnLineSegment({ lineA.first, lineB.first }, lineA.second))
	{
		return true;
	}

	if (orientations[1] == Orientation::Colinear && IsOnLineSegment({ lineA.first, lineB.first }, lineA.second))
	{
		return true;
	}

	if (orientations[2] == Orientation::Colinear && IsOnLineSegment({ lineA.second, lineB.second }, lineA.first))
	{
		return true;
	}

	if (orientations[3] == Orientation::Colinear && IsOnLineSegment({ lineA.second, lineB.second }, lineA.first))
	{
		return true;
	}

	return false;
}

template <size_t N, typename = std::enable_if_t<(N >= 3)>>
bool ContainsPoint(const Polygon<N>& polygon, const Point& point) noexcept
{
	const Line horizontalLevel{ point, { std::numeric_limits<int>::max(), point.y } };
	size_t currentPointIndex = 0;
	unsigned int intersectionCount = 0;

	do
	{
		const size_t nextPointIndex = (currentPointIndex + 1) % N;
		const Line currentPolygonSide{ polygon[currentPointIndex], polygon[nextPointIndex] };

		if (HaveIntersection(currentPolygonSide, horizontalLevel))
		{
			if (GetTriangleOrientation({ polygon[currentPointIndex], point, polygon[nextPointIndex] }) == Orientation::Colinear)
			{
				return IsOnLineSegment(currentPolygonSide, point);
			}

			++intersectionCount;
		}
	}
	while (currentPointIndex != 0);

	return intersectionCount % 2 == 0;
}

int main(int argc, char* argv[])
{
	const Polygon<5> polygon
	{
		Point{ 1, 1 },
		Point{ 2, 1 },
		Point{ 3, 2 },
		Point{ 2, 3 },
		Point{ 1, 2 }
	};

	std::cout << std::boolalpha;
	std::cout << ContainsPoint(polygon, { 2, 2 }) << "\n";
	std::cout << ContainsPoint(polygon, { 3, 3 }) << "\n";

	std::cin.get();

	return EXIT_SUCCESS;
}