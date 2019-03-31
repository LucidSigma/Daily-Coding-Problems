#include <cmath>
#include <iostream>

inline unsigned int GetExpectedCoinFlipRounds(const unsigned int coins) noexcept
{
	return static_cast<unsigned int>(std::ceil(std::log2(coins)));
}

int main(int argc, char* argv[])
{
	std::cout << GetExpectedCoinFlipRounds(100) << "\n";

	std::cin.get();

	return 0;
}