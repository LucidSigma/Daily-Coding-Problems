#include <cmath>
#include <iostream>
#include <iterator>
#include <optional>
#include <set>
#include <unordered_map>
#include <utility>
#include <vector>

std::unordered_map<int, int> GetMappedIndices(const std::vector<int>& numbers) noexcept
{
	std::unordered_map<int, int> mappedIndices;
	std::set<std::pair<unsigned int, int>> sortedIndices;

	for (unsigned int i = 0; i < numbers.size(); i++)
	{
		sortedIndices.insert({ i, numbers[i] });
	}

	unsigned int counter = 0;

	for (auto revIt = std::rbegin(sortedIndices); revIt != std::rend(sortedIndices); revIt++)
	{
		unsigned int minDistance = numbers.size();

		for (unsigned int i = counter + 1; i < sortedIndices.size(); i++)
		{
			auto offsetIterator = std::cbegin(sortedIndices);
			std::advance(offsetIterator, i);

			unsigned int currentDistance = std::abs(revIt->second - offsetIterator->second);

			if (currentDistance < minDistance)
			{
				minDistance = currentDistance;
				mappedIndices[revIt->second] = offsetIterator->second;
			}
		}

		counter++;
	}

	return mappedIndices;
}

inline std::optional<unsigned int> GetNearestLargerNumber(const std::vector<int>& numbers, const unsigned int index) noexcept
{
	const auto mappedIndices = GetMappedIndices(numbers);

	return mappedIndices.find(index) == std::cend(mappedIndices) ? std::nullopt : std::optional<unsigned int>(mappedIndices.at(index));
}

int main(int argc, char* argv[])
{
	std::cout << GetNearestLargerNumber({ 4, 1, 3, 5, 6 }, 0).value_or(-1) << "\n";

	std::cin.get();

	return 0;
}