#include <iostream>
#include <iterator>
#include <numeric>
#include <vector>

inline unsigned int FindDuplicate(const std::vector<unsigned int>& numbers) noexcept
{
	const unsigned int sumWithoutDuplicate = numbers.size() * (numbers.size() - 1) / 2;
	const unsigned int sumWithDuplicate = std::accumulate(std::cbegin(numbers), std::cend(numbers), 0);

	return sumWithDuplicate - sumWithoutDuplicate;
}

int main(int argc, char* argv[])
{
	std::cout << FindDuplicate({ 1, 2, 3, 4, 4, 5 }) << "\n";
	std::cout << FindDuplicate({ 1, 2, 3, 4, 5, 6, 7, 7, 8, 9, 10 }) << "\n";

	std::cin.get();

	return 0;
}
