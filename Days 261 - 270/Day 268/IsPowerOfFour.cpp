#include <cstdlib>
#include <iostream>

constexpr bool IsPowerOfFour(const unsigned int x) noexcept
{
	return (static_cast<unsigned int>(static_cast<int>(x) & -static_cast<int>(x)) & 0x55555554) == x || x == 1;
}

int main(int argc, char* argv[])
{
	std::cout << std::boolalpha;
	std::cout << IsPowerOfFour(1) << "\n";
	std::cout << IsPowerOfFour(4) << "\n";
	std::cout << IsPowerOfFour(5) << "\n";
	std::cout << IsPowerOfFour(16) << "\n";
	std::cout << IsPowerOfFour(64) << "\n";
	std::cout << IsPowerOfFour(100) << "\n";

	std::cin.get();

	return EXIT_SUCCESS;
}