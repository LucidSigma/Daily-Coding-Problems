#include <algorithm>
#include <cstddef>
#include <cstdlib>
#include <iostream>
#include <limits>
#include <vector>

unsigned int GetMinNumberOfJumpsHelper(const std::vector<unsigned int>& steps, const size_t currentIndex, const unsigned int currentJumpCount)
{
	if (currentIndex >= steps.size() - 1)
	{
		return currentJumpCount;
	}

	if (steps[currentIndex] == 0)
	{
		return std::numeric_limits<unsigned int>::max();
	}

	const unsigned int currentSteps = steps[currentIndex];
	unsigned int minJumpCount = std::numeric_limits<unsigned int>::max();

	for (unsigned int i = 1; i <= currentSteps; ++i)
	{
		minJumpCount = std::min(minJumpCount, GetMinNumberOfJumpsHelper(steps, currentIndex + i, currentJumpCount + 1));
	}

	return minJumpCount;
}

inline unsigned int GetMinNumberOfJumps(const std::vector<unsigned int>& steps)
{
	return GetMinNumberOfJumpsHelper(steps, 0, 0);
}

int main(int argc, char* argv[])
{
	std::cout << GetMinNumberOfJumps({ 6, 2, 4, 0, 5, 1, 1, 4, 2, 9 }) << "\n";

	std::cin.get();

	return EXIT_SUCCESS;
}