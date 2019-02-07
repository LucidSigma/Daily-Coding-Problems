#include <algorithm>
#include <iostream>
#include <limits>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

struct Path
{
	std::unordered_set<std::string> nodes;
	std::unordered_map<char, unsigned int> letterCounts;
};

std::vector<Path> GetMostVisitedNodeCountHelper(Path path, const std::string& node, std::unordered_map<std::string, std::unordered_set<std::string>>& adjacencies)
{
	if (path.nodes.find(node) != path.nodes.end())
	{
		return { path };
	}

	std::unordered_map<char, unsigned int> newLetterCounts = path.letterCounts;
	std::unordered_set<std::string> newNodes = path.nodes;
	newNodes.insert(node);
	
	if (newLetterCounts.find(node[0]) == newLetterCounts.end())
	{
		newLetterCounts[node[0]] = 0;
	}

	newLetterCounts[node[0]]++;

	Path newPath { newNodes, newLetterCounts };

	if (adjacencies.find(node) == adjacencies.end())
	{
		return { newPath };
	}

	std::vector<Path> paths;

	for (const auto& child : adjacencies[node])
	{
		std::vector<Path> newPaths = GetMostVisitedNodeCountHelper(newPath, child, adjacencies);
		paths.insert(paths.end(), newPaths.begin(), newPaths.end());
	}

	return paths;
}

unsigned int GetMostVisitedNodeCount(const std::string& inputString, const std::vector<std::pair<int, int>>& edges)
{
	std::unordered_map<char, unsigned int> letterCounts;
	std::vector<std::string> nodes;

	for (char c : inputString)
	{
		if (letterCounts.find(c) == letterCounts.end())
		{
			letterCounts[c] = 0;
		}

		letterCounts[c]++;

		nodes.push_back(c + std::to_string(letterCounts[c]));
	}

	std::unordered_map<std::string, std::unordered_set<std::string>> adjacencies;

	for (const auto[start, end] : edges)
	{
		if (nodes[start] != nodes[end] || (nodes[start].empty() && nodes[end].empty()))
		{
			adjacencies[nodes[start]].insert(nodes[end]);
		}
	}

	std::vector<Path> paths;
	Path graphPath;

	for (const auto& node : adjacencies)
	{
		std::vector<Path> newPaths = GetMostVisitedNodeCountHelper(graphPath, node.first, adjacencies);
		paths.insert(paths.end(), newPaths.begin(), newPaths.end());
	}

	unsigned int maxCount = 0;

	for (const Path& path : paths)
	{
		unsigned int pathMax = 0;

		for (const auto& letterCount : path.letterCounts)
		{
			pathMax = std::max(pathMax, letterCount.second);
		}

		maxCount = std::max(maxCount, pathMax);
	}

	static constexpr unsigned int InfiniteLoop = std::numeric_limits<unsigned int>::max();

	return maxCount > 0 ? maxCount : InfiniteLoop;
}

int main(int argc, char* argv[])
{
	std::cout << GetMostVisitedNodeCount("ABACA", { { 0, 1 }, { 0, 2 }, { 2, 3 }, { 3, 4 } }) << "\n";
	std::cout << GetMostVisitedNodeCount("A", { { 0, 0 } }) << "\n";

	std::cin.get();

	return 0;
}