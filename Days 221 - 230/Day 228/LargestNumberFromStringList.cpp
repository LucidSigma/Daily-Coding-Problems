#include <algorithm>
#include <cstddef>
#include <cstdlib>
#include <iostream>
#include <initializer_list>
#include <iterator>
#include <map>
#include <string>
#include <vector>

unsigned int GetLargestNumber(const std::initializer_list<unsigned int>& numbers) noexcept
{
	std::map<unsigned int, std::vector<std::string>> numberMap;

	for (const auto& number : numbers)
	{
		const std::string numberString = std::to_string(number);
		const unsigned int firstDigit = numberString[0] + '0';

		if (numberMap.find(firstDigit) == std::cend(numberMap))
		{
			numberMap[firstDigit] = std::vector<std::string>();
		}

		numberMap[firstDigit].push_back(numberString);
	}

	std::vector<std::vector<std::string>> sortedNumbers;
	sortedNumbers.reserve(numberMap.size());

	for (const auto& [_, numberList] : numberMap)
	{
		sortedNumbers.push_back(numberList);
	}

	std::sort(std::begin(sortedNumbers), std::end(sortedNumbers), [](const std::vector<std::string>& lhs, const std::vector<std::string>& rhs)
		{
			return lhs[0] > rhs[0];
		}
	);

	std::vector<std::string> largestNumberOrder;

	for (const auto& list : sortedNumbers)
	{
		if (list.size() == 1)
		{
			largestNumberOrder.insert(std::cend(largestNumberOrder), std::cbegin(list), std::cend(list));

			continue;
		}

		std::map<size_t, std::vector<std::string>> nextOrder;

		for (const auto& stringNumber : list)
		{
			if (nextOrder.find(stringNumber.length()) == std::cend(nextOrder))
			{
				nextOrder[stringNumber.length()] = std::vector<std::string>();
			}

			nextOrder[stringNumber.length()].push_back(stringNumber);
		}

		std::vector<std::vector<std::string>> sortedValues;
		sortedValues.reserve(nextOrder.size());

		for (const auto& [_, numberList] : nextOrder)
		{
			sortedValues.push_back(numberList);
		}

		std::sort(std::begin(sortedValues), std::end(sortedValues), [](const std::vector<std::string>& lhs, const std::vector<std::string>& rhs)
			{
				return lhs[0] < rhs[0];
			}
		);

		for (const auto& values : sortedValues)
		{
			largestNumberOrder.insert(std::cend(largestNumberOrder), std::cbegin(values), std::cend(values));
		}
	}

	std::string largestNumber;

	for (const auto& number : largestNumberOrder)
	{
		largestNumber += number;
	}

	return std::stoi(largestNumber);
}

int main(int argc, char* argv[])
{
	std::cout << GetLargestNumber({ 10, 7, 76, 415 }) << "\n";

	std::cin.get();

	return EXIT_SUCCESS;
}