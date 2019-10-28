#include <cstddef>
#include <cstdlib>
#include <functional>
#include <iostream>
#include <iterator>
#include <tuple>
#include <unordered_map>
#include <vector>

bool Is24PossibleHelper(const std::vector<unsigned int>& numbers)
{
	static constexpr unsigned int TargetNumber = 24u;

	if (numbers.size() == 1)
	{
		return numbers.front() == TargetNumber;
	}

	static const std::unordered_map<char, std::function<unsigned int(unsigned int, unsigned int)>> operators
	{
		{ '+', std::plus<unsigned int>() },
		{ '-', std::minus<unsigned int>() },
		{ '*', std::multiplies<unsigned int>() },
		{ '/', std::divides<unsigned int>() }
	};

	std::vector<std::vector<unsigned int>> expressions;

	for (size_t i = 0; i < numbers.size() - 1; ++i)
	{
		for (const auto& [symbol, operation] : operators)
		{
			const unsigned int lhs = numbers[i];
			const unsigned int rhs = numbers[i + 1];

			std::vector<unsigned int> currentExpression(std::cbegin(numbers), std::cbegin(numbers) + 1);
			currentExpression.push_back(operation(lhs, rhs));
			currentExpression.insert(std::cend(currentExpression), std::cbegin(numbers) + 2, std::cend(numbers));

			expressions.push_back(currentExpression);
		}
	}

	for (const auto& expression : expressions)
	{
		if (Is24PossibleHelper(expression))
		{
			return true;
		}
	}

	return false;
}

inline bool Is24Possible(const std::tuple<unsigned int, unsigned int, unsigned int, unsigned int>& numbers)
{
	const auto [a, b, c, d] = numbers;
	const std::vector<unsigned int> numberVector{ a, b, c, d };

	return Is24PossibleHelper(numberVector);
}

int main(const int argc, const char* const argv[])
{
	std::cout << std::boolalpha;
	std::cout << Is24Possible({ 5, 2, 7, 8 }) << "\n";

	std::cin.get();

	return EXIT_SUCCESS;
}