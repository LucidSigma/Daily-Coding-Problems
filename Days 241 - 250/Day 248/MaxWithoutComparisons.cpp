#include <cstddef>
#include <cstdlib>
#include <iostream>
#include <type_traits>

template <typename T, typename = std::enable_if_t<std::is_integral_v<T>>>
constexpr int MaxWithoutComparisons(const T a, const T b)
{
	constexpr size_t BitsPerByte = 8u;
	const T difference = a - b;
	const T sign = (difference >> (sizeof(T) * BitsPerByte - 1)) & 1;

	return a - (sign * difference);
}

int main(int argc, char* argv[])
{
	std::cout << MaxWithoutComparisons(10, 20) << "\n";
	std::cout << MaxWithoutComparisons(30, 20) << "\n";

	std::cin.get();

	return EXIT_SUCCESS;
}