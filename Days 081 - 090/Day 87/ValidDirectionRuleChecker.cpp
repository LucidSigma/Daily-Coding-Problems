#include <cstddef>
#include <iostream>
#include <map>
#include <stdexcept>
#include <string>
#include <unordered_set>
#include <utility>

struct Point;

namespace std
{
	template <>
	struct hash<Point>
	{
		size_t operator ()(const Point& point) const noexcept;
	};
}

struct Point
{
	const char value;
	std::map<char, std::unordered_set<Point>> neighbours
	{
			{ 'N', std::unordered_set<Point>() },
			{ 'S', std::unordered_set<Point>() },
			{ 'E', std::unordered_set<Point>() },
			{ 'W', std::unordered_set<Point>() }
	};

	explicit Point(char value) noexcept
		: value(value)
	{ }

	inline bool operator ==(const Point& rhs) const noexcept
	{
		return this->value == rhs.value && this->neighbours == rhs.neighbours;
	}
};

namespace std
{
	size_t hash<Point>::operator ()(const Point& point) const noexcept
	{
		return hash<char>()(point.value);
	}
}

class PointMap
{
private:
	inline static const std::map<char, char> oppositeDirections
	{
		{ 'N', 'S' },
		{ 'S', 'N' },
		{ 'E', 'W' },
		{ 'W', 'E' }
	};

public:
	void AddRule(Point& leftPoint, const std::string& direction, Point& rightPoint) const
	{
		for (char subdirection : direction)
		{
			if (rightPoint.neighbours[subdirection].find(leftPoint) != rightPoint.neighbours[subdirection].end() ||
				leftPoint.neighbours[subdirection].find(rightPoint) != leftPoint.neighbours[subdirection].end())
			{
				throw std::runtime_error("Invalid rule.");
			}

			for (Point point : leftPoint.neighbours.at(subdirection))
			{
				AddRule(point, std::to_string(subdirection), rightPoint);
			}
		}

		for (const char subdirection : direction)
		{
			rightPoint.neighbours[subdirection].insert(leftPoint);
			leftPoint.neighbours[oppositeDirections.at(subdirection)].insert(rightPoint);
		}
	}
};

int main(int argc, char* argv[])
{
	Point a('a');
	Point b('a');
	Point c('a');

	PointMap map;

	map.AddRule(a, "N", b);
	map.AddRule(b, "NE", c);

	try
	{
		map.AddRule(c, "N", a);
	}
	catch (const std::runtime_error&)
	{
		std::cout << "Invalid rule.\n";
	}

	a.neighbours.clear();
	b.neighbours.clear();

	map.AddRule(a, "NW", b);
	map.AddRule(a, "N", b);

	std::cin.get();

	return 0;
}