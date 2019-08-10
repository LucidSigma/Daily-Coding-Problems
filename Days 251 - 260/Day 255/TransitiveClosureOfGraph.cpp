#include <cstddef>
#include <cstdlib>
#include <iostream>
#include <unordered_map>
#include <vector>

using AdjacencyList = std::unordered_map<size_t, std::vector<size_t>>;
using TransitiveMatrix = std::vector<std::vector<bool>>;

void GetTransitiveClosureHelper(const size_t pathStart, const size_t currentNode, const AdjacencyList& adjacencyList, TransitiveMatrix& transitiveClosure)
{
	if (adjacencyList.at(currentNode).size() == 1)
	{
		return;
	}

	for (const auto adjacentNode : adjacencyList.at(currentNode))
	{
		if (pathStart == adjacentNode || currentNode == adjacentNode)
		{
			continue;
		}

		transitiveClosure[pathStart][currentNode] = true;
		GetTransitiveClosureHelper(pathStart, adjacentNode, adjacencyList, transitiveClosure);
	}
}

TransitiveMatrix GetTransitiveClosure(const AdjacencyList& adjacencyList)
{
	TransitiveMatrix transitiveClosure(adjacencyList.size(), std::vector<bool>(adjacencyList.size(), false));

	for (size_t i = 0; i < transitiveClosure.size(); ++i)
	{
		transitiveClosure[i][i] = true;
	}

	for (const auto& [node, _] : adjacencyList)
	{
		GetTransitiveClosureHelper(node, node, adjacencyList, transitiveClosure);
	}

	return transitiveClosure;
}

std::ostream& operator <<(std::ostream& outputStream, const TransitiveMatrix& transitiveMatrix)
{
	for (const auto& row : transitiveMatrix)
	{
		for (const auto value : row)
		{
			outputStream << value << " ";
		}

		outputStream << "\n";
	}

	return outputStream;
}

int main(int argc, char* argv[])
{
	const AdjacencyList adjacencyList
	{
		{ 0, { 0, 1, 3 } },
		{ 1, { 1, 3 } },
		{ 2, { 2 } },
		{ 3, { 3 } }
	};

	std::cout << GetTransitiveClosure(adjacencyList) << "\n";

	std::cin.get();

	return EXIT_SUCCESS;
}