#include <cstdlib>
#include <iostream>
#include <iterator>
#include <limits>
#include <unordered_map>
#include <utility>
#include <vector>

using ElevationMap = std::unordered_map<unsigned int, unsigned int>;
using PathMap = std::unordered_map<std::pair<unsigned int, unsigned int>, unsigned int>;
using CumulativePathMap = std::unordered_map<unsigned int, std::vector<std::pair<unsigned int, unsigned int>>>;

std::pair<PathMap, unsigned int> GetShortestHillPathHelper(const unsigned int destination, const ElevationMap& elevations, const CumulativePathMap& pathMap, const PathMap& currentPath, const ElevationMap& currentElevations, const unsigned int distance, const unsigned int switches)
{
	if (destination == 0 && !currentPath.empty())
	{
		return switches < 2 ? { currentPath, distance } : { currentPath, std::numeric_limits<unsigned int>::max() };
	}
}

std::vector<unsigned int> GetShortestHillPath(const ElevationMap& elevations, const PathMap& paths)
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


}

int main(int argc, char* argv[])
{
	

	std::cin.get();

	return EXIT_SUCCESS;
}