#include <algorithm>
#include <cstddef>
#include <cstdlib>
#include <functional>
#include <iostream>
#include <iterator>
#include <vector>

unsigned int FindHIndex(std::vector<unsigned int> citationCounts)
{
	std::sort(std::begin(citationCounts), std::end(citationCounts), std::greater<unsigned int>());

	for (size_t i = 0; i < citationCounts.size(); ++i)
	{
		if (i >= citationCounts[i])
		{
			return i;
		}
	}

	return citationCounts.back();
}

int main(int argc, char* argv[])
{
	std::cout << FindHIndex({ 4, 3, 0, 1, 5 }) << "\n";

	std::cin.get();

	return EXIT_SUCCESS;
}