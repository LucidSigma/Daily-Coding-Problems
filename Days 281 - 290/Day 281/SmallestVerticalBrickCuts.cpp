#include <cstdlib>
#include <iostream>
#include <iterator>
#include <map>
#include <vector>

unsigned int GetSmallestBrickCutLocation(std::vector<std::vector<unsigned int>> brickWall)
{
	for (auto& layer : brickWall)
	{
		unsigned int cumulativeLayerLength = 0;

		for (auto& brick : layer)
		{
			brick += cumulativeLayerLength;
			cumulativeLayerLength = brick;
		}

		layer = std::vector(std::cbegin(layer), std::cend(layer) - 1);
	}

	std::map<unsigned int, unsigned int> brickCutCounter;

	for (const auto& layer : brickWall)
	{
		const unsigned int layerLength = layer.front();

		if (brickCutCounter.find(layerLength) == std::cend(brickCutCounter))
		{
			brickCutCounter[layerLength] = 0;
		}

		++brickCutCounter[layerLength];
	}

	return brickWall.size() - std::cbegin(brickCutCounter)->first;
}

int main(int argc, char* argv[])
{
	const std::vector<std::vector<unsigned int>> brickWall
	{
		{ 3, 5, 1, 1 },
		{ 2, 3, 3, 2 },
		{ 5, 5 },
		{ 4, 4, 2 },
		{ 1, 3, 3, 3 },
		{ 1, 1, 6, 1, 1 }
	};

	std::cout << GetSmallestBrickCutLocation(brickWall) << "\n";

	std::cin.get();

	return EXIT_SUCCESS;
}