#include <algorithm>
#include <iostream>
#include <iterator>
#include <vector>

std::vector<int> GetNextPermutation(std::vector<int> permutation) noexcept
{
	int i;

	for (i = permutation.size() - 1; i >= 0; i--)
	{
		if (i > 0 && permutation[i - 1] < permutation[i])
		{
			break;
		}
	}

	if (i == 0)
	{
		std::reverse(std::begin(permutation), std::end(permutation));

		return permutation;
	}
	else
	{
		for (int j = permutation.size() - 1; j >= i; j--)
		{
			if (permutation[j] > permutation[i - 1])
			{
				std::swap(permutation[j], permutation[i - 1]);

				break;
			}
		}

		std::vector<int> subVector(std::rbegin(permutation), std::rend(permutation) - i);

		for (unsigned int j = 0; j < subVector.size(); j++)
		{
			permutation[i + j] = subVector[j];
		}
	}

	return permutation;
}

template <typename T>
void PrintVector(const std::vector<T>& values) noexcept
{
	for (const auto& value : values)
	{
		std::cout << value << " ";
	}

	std::cout << "\n";
}

int main(int argc, char* argv[])
{
	PrintVector(GetNextPermutation({ 1, 2, 3 }));

	std::cin.get();

	return 0;
}