#include <cstddef>
#include <cstdlib>
#include <iostream>
#include <iterator>
#include <unordered_set>
#include <vector>

bool ContainsPythagoreanTriple(const std::vector<unsigned int>& numbers)
{
	std::unordered_set<unsigned int> squaredNumbers;

	for (const auto number : numbers)
	{
		squaredNumbers.insert(number * number);
	}

	for (size_t i = 0; i < numbers.size() - 1; ++i)
	{
		for (size_t j = i + 1; j < numbers.size(); ++j)
		{
			if (const unsigned int squaredSum = (numbers[i] * numbers[i]) + (numbers[j] * numbers[j]);
				squaredNumbers.find(squaredSum) != std::cend(squaredNumbers))
			{
				return true;
			}
		}
	}

	return false;
}

int main(int argc, char* argv[])
{
	std::cout << std::boolalpha;
	std::cout << ContainsPythagoreanTriple({ 1, 2, 3, 4 }) << "\n";
	std::cout << ContainsPythagoreanTriple({ 1, 2, 3, 4, 5, 6, 7 }) << "\n";

	std::cin.get();

	return EXIT_SUCCESS;
}