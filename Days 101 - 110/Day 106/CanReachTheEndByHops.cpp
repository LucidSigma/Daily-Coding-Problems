#include <iostream>
#include <iterator>
#include <unordered_set>
#include <vector>

bool CanReachTheEnd(const std::vector<int>& hops) noexcept
{
	unsigned int currentIndex = 0;
	std::unordered_set<int> visitedIndices;

	while (currentIndex < hops.size() - 1)
	{
		if (currentIndex < 0 || hops[currentIndex] == 0)
		{
			return false;
		}

		currentIndex += hops[currentIndex];

		if (visitedIndices.find(currentIndex) == std::cend(visitedIndices))
		{
			visitedIndices.insert(currentIndex);
		}
		else
		{
			return false;
		}
	}

	return true;
}

int main()
{
	std::cout << std::boolalpha;
	std::cout << CanReachTheEnd({ 2, 0, 1, 0 }) << "\n";
	std::cout << CanReachTheEnd({ 1, 1, 0, 1 }) << "\n";
	std::cout << CanReachTheEnd({ 2, 2, -1, 0 }) << "\n";
	std::cout << CanReachTheEnd({ 1, -1, 1, 1 }) << "\n";

	std::cin.get();

	return 0;
}