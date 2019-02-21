#include <iostream>
#include <type_traits>

template <int B, typename = std::enable_if_t<(B == 0) || (B == 1)>>
constexpr int GetXOrYFromB(int x, int y) noexcept
{
	return x * B + y * (1 - B);
}

int main(int argc, char* argv[])
{
	std::cout << GetXOrYFromB<0>(16, 32) << "\n";
	std::cout << GetXOrYFromB<1>(16, 32) << "\n";

	std::cout << GetXOrYFromB<0>(10, 40) << "\n";
	std::cout << GetXOrYFromB<1>(10, 40) << "\n";

	std::cout << GetXOrYFromB<0>(-27, 81) << "\n";
	std::cout << GetXOrYFromB<1>(-27, 81) << "\n";

	std::cin.get();

	return 0;
}