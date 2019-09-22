#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <iterator>
#include <string>
#include <unordered_map>
#include <vector>

using CostsMap = std::unordered_map<std::string, std::unordered_map<std::string, unsigned int>>;

unsigned int GetMinPipeCostHelper(const CostsMap& pipeCosts, const CostsMap& houses, const unsigned int totalCost)
{
	if (houses.empty())
	{
		return totalCost;
	}

	std::vector<unsigned int> costs;
	std::vector<std::string> startingHouses;
	
	for (const auto& [house, _] : pipeCosts)
	{
		if (houses.find(house) == std::cend(houses))
		{
			startingHouses.push_back(house);
		}
	}

	for (const auto& start : startingHouses)
	{
		std::vector<std::string> endingHouses;

		for (const auto& [startHouse, _] : pipeCosts.at(start))
		{
			if (houses.find(startHouse) != std::cend(houses))
			{
				endingHouses.push_back(startHouse);
			}
		}

		for (const auto& end : endingHouses)
		{
			auto adjacentHouses = houses;
			adjacentHouses.erase(end);

			const unsigned int currentCost = GetMinPipeCostHelper(pipeCosts, adjacentHouses, totalCost + pipeCosts.at(start).at(end));
			costs.push_back(currentCost);
		}
	}

	return *std::min_element(std::cbegin(costs), std::cend(costs));
}

unsigned int GetMinPipeCost(const CostsMap& pipeCosts)
{
	auto houses = pipeCosts;
	houses.erase("plant");

	return GetMinPipeCostHelper(pipeCosts, houses, 0);
}

int main(int argc, char* argv[])
{
	const CostsMap pipes
	{
		{ "plant", { { "A", 1 }, { "B", 5 }, { "C", 20 } } },
		{ "A", { { "C", 15 } } },
		{ "B", { { "C", 10 } } },
		{ "C", { } }
	};

	std::cout << GetMinPipeCost(pipes) << "\n";

	std::cin.get();

	return EXIT_SUCCESS;
}