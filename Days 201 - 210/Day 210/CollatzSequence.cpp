#include <iostream>
#include <utility>

unsigned int RunCollatzSequence(const unsigned int n) noexcept
{
	if (n == 1)
	{
		return 0;
	}

	return 1 + (n % 2 == 0 ? RunCollatzSequence(n / 2) : RunCollatzSequence(3 * n + 1));
}

std::pair<unsigned int, unsigned int> GetLongestCollatzSequence() noexcept
{
	std::pair<unsigned int, unsigned int> longestSequence{ 0, 0 };

	for (unsigned int i = 1; i <= 1'000'000; ++i)
	{
		const unsigned int currentSequenceLength = RunCollatzSequence(i);

		if (currentSequenceLength > longestSequence.second)
		{
			longestSequence = { i, currentSequenceLength };
		}
	}

	return longestSequence;
}

int main(int argc, char* argv[])
{
	const auto [longest, steps] = GetLongestCollatzSequence();

	std::cout << "Longest sequence is " << longest << " with " << steps << " steps.\n";

	std::cin.get();

	return 0;
}