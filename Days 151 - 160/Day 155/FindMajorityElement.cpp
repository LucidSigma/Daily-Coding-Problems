#include <iostream>
#include <iterator>
#include <stdexcept>
#include <unordered_map>
#include <vector>

int GetMajorityElement(const std::vector<int>& numbers)
{
	std::unordered_map<int, unsigned int> elementCounts;
	const unsigned int majorityThreshold = numbers.size() / 2;

	for (const auto number : numbers)
	{
		if (elementCounts.find(number) == std::cend(elementCounts))
		{
			elementCounts[number] = 0;
		}

		++elementCounts[number];

		if (elementCounts[number] >= majorityThreshold)
		{
			return number;
		}
	}

	throw std::invalid_argument("No majority element exists in list.");
}

int main(int argc, char* argv[])
{
	std::cout << GetMajorityElement({ 1, 2, 1, 1, 3, 4, 0 }) << "\n";
	
	std::cin.get();

	return 0;
}