#include <cstddef>
#include <cstdlib>
#include <iostream>
#include <iterator>
#include <vector>

int FindPeakElement(const std::vector<int>& values)
{
	if (values.size() == 1)
	{
		return values.front();
	}

	const size_t midpointIndex = values.size() / 2;

	if (midpointIndex > 0 && values[midpointIndex] > values[midpointIndex - 1] && 
		midpointIndex < values.size() - 1 && values[midpointIndex] > values[midpointIndex + 1])
	{
		return values[midpointIndex];
	}

	return midpointIndex > 0 && values[midpointIndex] > values[midpointIndex - 1] 
		   ? FindPeakElement(std::vector<int>(std::cbegin(values), std::cbegin(values) + midpointIndex))
		   : FindPeakElement(std::vector<int>(std::cbegin(values) + midpointIndex + 1, std::cend(values)));
}

int main(const int argc, const char* const argv[])
{
	std::cout << FindPeakElement({ 1, 7, 0, 4, 3, 5, 6, 2 }) << "\n";

	std::cin.get();

	return EXIT_SUCCESS;
}