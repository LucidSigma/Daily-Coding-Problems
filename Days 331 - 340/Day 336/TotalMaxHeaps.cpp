#include <cstdlib>
#include <iostream>
#include <type_traits>
#include <vector>

template <typename N = unsigned long, typename = std::enable_if_t<std::is_unsigned_v<N>>>
constexpr N Factorial(const N max)
{
	N factorial = 1;

	for (N i = 2; i <= max; ++i)
	{
		factorial *= i;
	}

	return factorial;
}

template <typename N = unsigned long, typename = std::enable_if_t<std::is_unsigned_v<N>>>
constexpr N BinomialCoefficient(const N n, const N k)
{
	return Factorial(n) / (Factorial(k) * Factorial(n - k));
}

constexpr unsigned long FindTotalPossibleMaxHeapsHelper(const unsigned long count)
{
	if (count <= 1)
	{
		return 1;
	}

	const unsigned long n1 = count / 2;
	unsigned long n2 = n1 - 1;

	if (n1 + n2 == count)
	{
		--n2;
	}

	return BinomialCoefficient(count, n1) * FindTotalPossibleMaxHeapsHelper(n1) * FindTotalPossibleMaxHeapsHelper(n2);
}

constexpr unsigned long FindTotalPossibleMaxHeaps(const std::vector<int>& numbers)
{
	return FindTotalPossibleMaxHeapsHelper(numbers.size());
}

int main(const int argc, const char* const argv[])
{
	std::cout << FindTotalPossibleMaxHeaps({ 1, 2, 3 }) << "\n";

	std::cin.get();

	return EXIT_SUCCESS;
}