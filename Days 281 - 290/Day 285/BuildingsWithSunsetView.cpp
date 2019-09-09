#include <cstdlib>
#include <iostream>
#include <vector>

unsigned int BuildingCountWithSunsetView(const std::vector<unsigned int>& buildings)
{
	std::vector<unsigned int> buildingsWithView;

	for (const auto building : buildings)
	{
		if (!buildingsWithView.empty() && buildingsWithView.back() < building)
		{
			buildingsWithView.pop_back();
		}

		buildingsWithView.push_back(building);
	}

	return buildingsWithView.size();
}

int main(int argc, char* argv[])
{
	std::cout << BuildingCountWithSunsetView({ 3, 7, 8, 3, 6, 1 }) << "\n";

	std::cin.get();

	return EXIT_SUCCESS;
}