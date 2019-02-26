#include <iostream>
#include <vector>

std::vector<int> GetSumSubset(const std::vector<int>& numbers, int sum) noexcept
{
	if (numbers.empty())
	{
		return { };
	}

	if (numbers[0] == sum)
	{
		return { numbers[0] };
	}

	std::vector<int> withFirstNumber = GetSumSubset(std::vector<int>(numbers.begin() + 1, numbers.end()), sum - numbers[0]);

	if (!withFirstNumber.empty())
	{
		return withFirstNumber.push_back(numbers[0]), withFirstNumber;
	}
	else
	{
		return GetSumSubset(std::vector<int>(numbers.begin() + 1, numbers.end()), sum);
	}
}

template <typename T>
void PrintVector(const std::vector<T>& values)
{
	for (const auto& value : values)
	{
		std::cout << value << " ";
	}

	std::cout << "\n";
}

int main(int argc, const char* argv[])
{
	PrintVector(GetSumSubset({ 12, 1, 61, 5, 9, 2 }, 24));

	std::cin.get();

	return 0;
}