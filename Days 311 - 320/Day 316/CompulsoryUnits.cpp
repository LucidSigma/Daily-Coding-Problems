#include <algorithm>
#include <cstddef>
#include <cstdlib>
#include <iostream>
#include <iterator>
#include <vector>

using Unit = size_t;

unsigned int GetCompulsoryUnitsHelper(const Unit unit, const std::vector<Unit>& compulsoryUnits)
{
	if (unit == 0 || std::find(std::cbegin(compulsoryUnits), std::cend(compulsoryUnits), unit) != std::cend(compulsoryUnits))
	{
		return 1;
	}

	unsigned int productionCount = 0;

	for (size_t i = 0; i < compulsoryUnits.size(); ++i)
	{
		if (unit % compulsoryUnits[i] == 0)
		{
			productionCount += GetCompulsoryUnitsHelper(unit / compulsoryUnits[i], std::vector<Unit>(std::cbegin(compulsoryUnits) + i, std::cend(compulsoryUnits)));
		}
	}

	return productionCount;
}

std::vector<Unit> GetCompulsoryUnits(const std::vector<unsigned int>& changeProductionCounts)
{
	std::vector<Unit> compulsoryUnits;

	for (Unit i = 0; i < changeProductionCounts.size(); ++i)
	{
		if (changeProductionCounts[i] == 1 && i > 0)
		{
			compulsoryUnits.push_back(i);
		}
	}

	for (Unit i = 0; i < changeProductionCounts.size(); ++i)
	{
		if (GetCompulsoryUnitsHelper(i, compulsoryUnits) == changeProductionCounts[i] - 1)
		{
			compulsoryUnits.push_back(i);
		}
	}

	return compulsoryUnits;
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

int main(const int argc, const char* const argv[])
{
	std::cout << GetCompulsoryUnits({ 1, 0, 1, 1, 2 }) << "\n";

	std::cin.get();

	return EXIT_SUCCESS;
}