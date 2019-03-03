#include <iostream>
#include <iterator>
#include <vector>

std::vector<std::vector<int>> GetAllPermutations(const std::vector<int>& numbers) noexcept
{
	if (numbers.size() <= 1)
	{
		return { numbers };
	}

	std::vector<std::vector<int>> permutationsList;

	for (unsigned int i = 0; i < numbers.size(); i++)
	{
		std::vector<int> currentPermutation(numbers);
		currentPermutation.erase(std::begin(currentPermutation) + i);

		auto childPermutations = GetAllPermutations(currentPermutation);

		for (auto& permutation : childPermutations)
		{
			permutation.push_back(numbers[i]);
			permutationsList.push_back(permutation);
		}
	}

	return permutationsList;
}

template <typename T>
void PrintVectorOfVectors(const std::vector<std::vector<T>>& vectors) noexcept
{
	for (const auto& vector : vectors)
	{
		std::cout << "[ ";

		for (const T& value : vector)
		{
			std::cout << value << " ";
		}

		std::cout << "]\n";
	}
}

int main(int argc, char* argv[])
{
	PrintVectorOfVectors(GetAllPermutations({ 1, 2, 3 }));

	std::cin.get();

	return 0;
}