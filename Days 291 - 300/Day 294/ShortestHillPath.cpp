#include <cstddef>
#include <cstdlib>
#include <functional>
#include <iostream>
#include <iterator>
#include <limits>
#include <unordered_map>
#include <utility>
#include <vector>

using ElevationMap = std::unordered_map<unsigned int, unsigned int>;
using PathMap = std::unordered_map<std::pair<unsigned int, unsigned int>, unsigned int>;
using CumulativePathMap = std::unordered_map<unsigned int, std::vector<std::pair<unsigned int, unsigned int>>>;

template <>
struct std::hash<std::pair<unsigned int, unsigned int>>
{
	inline size_t operator ()(const std::pair<unsigned int, unsigned int>& values) const noexcept
	{
		return std::hash<unsigned int>()(values.first) ^ std::hash<unsigned int>()(values.second);
	}
};

std::pair<std::vector<unsigned int>, unsigned int> GetShortestHillPathHelper(const unsigned int destination, const ElevationMap& elevations, const CumulativePathMap& pathMap, std::vector<unsigned int> currentPath, std::vector<unsigned int> currentElevations, const unsigned int totalDistance, const unsigned int directionSwitchCount)
{
	if (destination == 0 && !currentPath.empty())
	{
		return directionSwitchCount < 2 ? std::pair<std::vector<unsigned int>, unsigned int>{ currentPath, totalDistance } : std::pair<std::vector<unsigned int>, unsigned int>{ currentPath, std::numeric_limits<unsigned int>::max() };
	}

	unsigned int minDistance = std::numeric_limits<unsigned int>::max();
	std::vector<unsigned int> minPath;

	for (const auto [source, distance] : pathMap.at(destination))
	{
		if (source == destination)
		{
			continue;
		}

		currentPath.insert(std::cbegin(currentPath), { source });
		currentElevations.insert(std::cbegin(currentElevations), { elevations.at(destination) });
		const unsigned int newDirectionSwitchCount = !currentElevations.empty() && elevations.at(source) > currentElevations[0] ? directionSwitchCount + 1 : directionSwitchCount;
		const auto [newPath, newDistance] = GetShortestHillPathHelper(source, elevations, pathMap, currentPath, currentElevations, totalDistance + distance, newDirectionSwitchCount);

		if (newDistance < minDistance)
		{
			minDistance = newDistance;
			minPath = newPath;
		}
	}

	return { minPath, minDistance };
}

std::pair<std::vector<unsigned int>, unsigned int> GetShortestHillPath(const ElevationMap& elevations, const PathMap& paths)
{
	CumulativePathMap pathMap;

	for (const auto [path, distance] : paths)
	{
		const auto [source, destination] = path;

		if (pathMap.find(destination) == std::cend(pathMap))
		{
			pathMap[destination] = { };
		}

		pathMap[destination].emplace_back(source, distance);
	}

	return GetShortestHillPathHelper(0, elevations, pathMap, { }, { }, 0, 0);
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
	const ElevationMap elevations
	{
		{ 0, 5 },
		{ 1, 25 },
		{ 2, 15 },
		{ 3, 20 },
		{ 4, 10 }
	};

	const PathMap paths
	{
		{ { 0, 1 }, 10 },
		{ { 0, 2 }, 8 },
		{ { 0, 3 }, 15 },
		{ { 1, 3 }, 12 },
		{ { 2, 4 }, 10 },
		{ { 3, 4 }, 5 },
		{ { 3, 0 }, 17 },
		{ { 4, 0 }, 10 }
	};

	const auto [path, distance] = GetShortestHillPath(elevations, paths);

	std::cout << "Path is " << path << " with a total distance of " << distance << ".\n";

	std::cin.get();

	return EXIT_SUCCESS;
}