#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <iostream>
#include <iterator>
#include <limits>
#include <vector>

using Mouse = int;
using Hole = int;

unsigned int GetOptimalMiceStepCountHelper(const std::vector<Mouse>& mice, const std::vector<Hole>& holes, const unsigned int largestStep)
{
	if (mice.empty())
	{
		return largestStep;
	}

	std::vector<unsigned int> minSteps;

	for (const auto hole : holes)
	{
		const unsigned int steps = std::abs(mice.front() - hole);

		auto newHoles = holes;
		newHoles.erase(std::remove(std::begin(newHoles), std::end(newHoles), hole));

		minSteps.push_back(GetOptimalMiceStepCountHelper(std::vector<Mouse>(std::cbegin(mice) + 1, std::cend(mice)), newHoles, std::max(largestStep, steps)));
	}

	return *std::min_element(std::cbegin(minSteps), std::cend(minSteps));
}

inline unsigned int GetOptimalMiceStepCount(const std::vector<Mouse>& mice, const std::vector<Hole>& holes)
{
	return GetOptimalMiceStepCountHelper(mice, holes, std::numeric_limits<unsigned int>::min());
}

int main(const int argc, const char* const argv[])
{
	std::cout << GetOptimalMiceStepCount({ 1, 4, 9, 15 }, { 10, -5, 0, 16 }) << "\n";

	std::cin.get();

	return EXIT_SUCCESS;
}