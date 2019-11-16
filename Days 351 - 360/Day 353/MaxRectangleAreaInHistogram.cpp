#include <algorithm>
#include <cstddef>
#include <cstdlib>
#include <iostream>
#include <vector>

unsigned int GetMaxAreaInHistogramHelper(const std::vector<unsigned int>& histogram, const size_t startIndex, const size_t endIndex)
{
	if (startIndex == endIndex)
	{
		return 0;
	}

	const unsigned int currentArea = (endIndex - startIndex) * *std::min_element(std::cbegin(histogram) + startIndex, std::cbegin(histogram) + endIndex);
	const unsigned int leftArea = GetMaxAreaInHistogramHelper(histogram, startIndex, endIndex - 1);
	const unsigned int rightArea = GetMaxAreaInHistogramHelper(histogram, startIndex + 1, endIndex);

	return std::max(currentArea, std::max(leftArea, rightArea));
}

inline unsigned int GetMaxAreaInHistogram(const std::vector<unsigned int>& histogram)
{
	return GetMaxAreaInHistogramHelper(histogram, 0, histogram.size());
}

int main(const int argc, const char* const argv[])
{
	std::cout << GetMaxAreaInHistogram({ 1, 3, 2, 5 }) << "\n";

	std::cin.get();

	return EXIT_SUCCESS;
}