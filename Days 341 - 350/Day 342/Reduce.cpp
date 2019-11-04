#include <cstdlib>
#include <functional>
#include <iostream>
#include <vector>

template <typename T>
using BinaryFunction = std::function<T(T, T)>;

template <typename T>
T Reduce(const std::vector<T>& values, const BinaryFunction<T>& function, const T&& initialValue)
{
	T result = initialValue;

	for (const auto& value : values)
	{
		result = function(result, value);
	}

	return result;
}

inline int Add(int a, int b) noexcept
{
	return a + b;
}

inline int Sum(const std::vector<int>& values)
{
	return Reduce<int>(values, Add, 0);
}

int main(const int argc, const char* const argv[])
{
	std::cout << Sum({ 1, 2, 3, 4, 5 }) << "\n";

	std::cin.get();

	return EXIT_SUCCESS;
}