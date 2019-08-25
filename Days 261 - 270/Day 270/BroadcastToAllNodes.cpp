#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <iterator>
#include <tuple>
#include <unordered_map>
#include <utility>
#include <vector>

using Node = unsigned int;
using Edge = std::tuple<Node, Node, unsigned int>;

unsigned int GetShortestTime(const unsigned int targetNode, const std::unordered_map<Node, std::vector<std::pair<Node, unsigned int>>>& sourceNodes)
{
	if (targetNode == 0)
	{
		return 0;
	}

	const auto& candidateTargetTimes = sourceNodes.at(targetNode);
	std::vector<unsigned int> times;

	for (const auto [candidateDestination, candidateTime] : candidateTargetTimes)
	{
		times.push_back(candidateTime + GetShortestTime(candidateDestination, sourceNodes));
	}

	return *std::min_element(std::cbegin(times), std::cend(times));
}

unsigned int GetBroadcastTime(const std::vector<Edge>& edges, const unsigned int nodeCount)
{
	std::unordered_map<Node, std::vector<std::pair<Node, unsigned int>>> sourceNodes;

	for (const auto [source, destination, time] : edges)
	{
		if (sourceNodes.find(destination) == std::cend(sourceNodes))
		{
			sourceNodes[destination] = { };
		}

		sourceNodes[destination].emplace_back(source, time);
	}

	std::vector<unsigned int> times;

	for (unsigned int i = 1; i <= nodeCount; ++i)
	{
		times.push_back(GetShortestTime(i, sourceNodes));
	}

	return *std::max_element(std::cbegin(times), std::cend(times));
}

int main(int argc, char* argv[])
{
	const std::vector<Edge> edges
	{
		{ 0, 1, 5 },
		{ 0, 2, 3 },
		{ 0, 5, 4 },
		{ 1, 3, 8 },
		{ 2, 3, 1 },
		{ 3, 5, 10 },
		{ 3, 4, 5 }
	};

	std::cout << GetBroadcastTime(edges, 5) << "\n";

	std::cin.get();

	return EXIT_SUCCESS;
}