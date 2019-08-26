#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <iterator>
#include <vector>

template <typename T>
inline bool IsInList(const std::vector<T>& list, const T&& value)
{
	const auto upperBoundIterator = std::upper_bound(std::cbegin(list), std::cend(list), value);

	return upperBoundIterator != std::cend(list) && *(upperBoundIterator - 1) == value;
}

int main(int argc, char* argv[])
{
	std::cout << std::boolalpha;
	std::cout << IsInList({ 1, 3, 6, 7, 9, 10, 15, 19, 24 }, 15) << "\n";
	std::cout << IsInList({ 1, 3, 6, 7, 9, 10, 15, 19, 24 }, 16) << "\n";

	std::cin.get();

	return EXIT_SUCCESS;
}