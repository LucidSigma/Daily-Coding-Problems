#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <iterator>
#include <vector>

unsigned int GetRequiredEggDrops(const unsigned int n, const unsigned int k) noexcept
{
	if (n == 0 || n == 1 || k == 1)
	{
		return n;
	}

	std::vector<unsigned int> candidateDropCounts;

	for (unsigned int i = 1; i <= n; ++i)
	{
		const unsigned int optimalDropCount = std::max(GetRequiredEggDrops(i - 1, k - 1), GetRequiredEggDrops(n - i, k));

		candidateDropCounts.push_back(optimalDropCount);
	}

	return *std::min_element(std::cbegin(candidateDropCounts), std::cend(candidateDropCounts)) + 1;
}

int main(int argc, char* argv[])
{
	std::cout << GetRequiredEggDrops(1, 5) << "\n";

	std::cin.get();

	return EXIT_SUCCESS;
}