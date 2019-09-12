#include <array>
#include <cstddef>
#include <cstdlib>
#include <functional>
#include <iostream>
#include <tuple>

bool PlayerOneForcedWin(const std::tuple<unsigned int, unsigned int, unsigned int>& startingHeaps)
{
	const auto [a, b, c] = startingHeaps;
	const std::array<std::reference_wrapper<const unsigned int>, 3> heapArray{ a, b, c };
	unsigned int flag = a;

	for (size_t i = 1; i < heapArray.size(); ++i)
	{
		flag ^= heapArray[i];
	}

	for (const auto heap : heapArray)
	{
		if ((heap ^ flag) < heap)
		{
			return true;
		}
	}

	return false;
}

int main(int argc, char* argv[])
{
	std::cout << std::boolalpha;
	std::cout << PlayerOneForcedWin({ 3, 4, 5 }) << "\n";

	std::cin.get();

	return EXIT_SUCCESS;
}