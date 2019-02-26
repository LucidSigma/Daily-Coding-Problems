#include <cmath>
#include <iostream>
#include <vector>

template <typename T>
std::vector<std::vector<T>> CreatePowerSet(const std::vector<T>& set) noexcept
{
	unsigned int subsets = static_cast<unsigned int>(std::pow(2, set.size()));

	std::vector<std::vector<T>> powerSet;
	powerSet.reserve(subsets);

	for (unsigned int i = 0; i < subsets; i++)
	{
		std::vector<T> currentSubset;
		currentSubset.reserve(set.size());

		for (unsigned int j = 0; j < subsets; j++)
		{
			if (int mask = 1 << j; (i & mask) == mask)
			{
				currentSubset.push_back(set[j]);
			}
		}

		powerSet.push_back(currentSubset);
	}

	return powerSet;
}

template <typename T>
std::ostream& operator <<(std::ostream& os, const std::vector<T>& set)
{
	os << "{";

	for (unsigned int i = 0; i < set.size(); i++)
	{
		os << " " << set[i];

		if (i != set.size() - 1)
		{
			os << ",";
		}
	}

	os << " }";

	return os;
}

int main(int argc, const char* argv[])
{
	std::vector<int> values { 1, 2, 3 };
	auto powerSet = CreatePowerSet(values);

	std::cout << powerSet << "\n";

	std::cin.get();

	return 0;
}