#include <algorithm>
#include <cstddef>
#include <cstdlib>
#include <iostream>
#include <limits>
#include <tuple>
#include <utility>
#include <vector>

using Building = std::tuple<unsigned int, unsigned int, unsigned int>;
using Coordinate = std::pair<unsigned int, unsigned int>;

unsigned int GetSkylineWidth(const std::vector<Building>& buildings)
{
	unsigned int minLeft = std::numeric_limits<unsigned int>::max();
	unsigned int maxRight = 0;

	for (const auto [left, right, _] : buildings)
	{
		minLeft = std::min(left, minLeft);
		maxRight = std::max(right, maxRight);
	}

	return maxRight - minLeft + 1;
}

std::vector<Coordinate> GetSkylineCoordinates(const std::vector<Building>& buildings)
{
	const unsigned int skylineWidth = GetSkylineWidth(buildings);
	std::vector<unsigned int> maxHeights(skylineWidth, 0);

	for (const auto [left, right, height] : buildings)
	{
		for (unsigned int i = left; i < right; ++i)
		{
			maxHeights[i] = std::max(height, maxHeights[i]);
		}
	}

	std::vector<Coordinate> skylineCoordinates;
	unsigned int previousHeight = 0;

	for (size_t i = 0; i < maxHeights.size(); ++i)
	{
		if (skylineCoordinates.empty() || previousHeight != maxHeights[i])
		{
			skylineCoordinates.emplace_back(i, maxHeights[i]);
		}

		previousHeight = maxHeights[i];
	}

	return skylineCoordinates;
}

inline std::ostream& operator <<(std::ostream& outputStream, const Coordinate& coordinate)
{
	outputStream << "( " << coordinate.first << ", " << coordinate.second << " )";

	return outputStream;
}

template <typename T>
std::ostream& operator <<(std::ostream& outputStream, const std::vector<T>& values)
{
	for (const auto& value : values)
	{
		outputStream << value << " ";
	}

	return outputStream;
}

int main(int argc, char* argv[])
{
	std::cout << GetSkylineCoordinates({ { 0, 15, 3 }, { 4, 11, 5 }, { 19, 23, 4 } }) << "\n";

	std::cin.get();

	return EXIT_SUCCESS;
}