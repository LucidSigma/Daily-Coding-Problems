#include <bitset>
#include <cstdint>
#include <iostream>

static constexpr std::uint8_t EvenBits{ 0b10101010u };
static constexpr std::uint8_t OddBits{ 0b01010101u };

constexpr std::uint8_t SwapEvenAndOddBits(std::uint8_t number) noexcept
{
	return ((number & EvenBits) >> 1) | ((number & OddBits) << 1);
}

int main(int argc, char* argv[])
{
	std::cout << std::bitset<8u>(SwapEvenAndOddBits(0b10101010)) << "\n";
	std::cout << std::bitset<8u>(SwapEvenAndOddBits(0b11100010)) << "\n";

	std::cin.get();

	return 0;
}