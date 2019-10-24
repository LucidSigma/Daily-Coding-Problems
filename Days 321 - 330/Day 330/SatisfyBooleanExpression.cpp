#include <algorithm>
#include <bitset>
#include <cmath>
#include <cstddef>
#include <cstdlib>
#include <iostream>
#include <iterator>
#include <optional>
#include <string>
#include <unordered_map>
#include <vector>

#include "MathExpr.h"

std::u32string ReplaceAll(std::u32string string, const std::u32string& from, const std::u32string& to)
{
	size_t startIndex = string.find(from, 0);

	while (startIndex != std::string::npos)
	{
		string.replace(startIndex, from.length(), to);
		startIndex += to.length();

		startIndex = string.find(from, startIndex);
	}

	return string;
}

std::optional<std::unordered_map<char32_t, bool>> SatisfyBooleanFormula(const std::u32string& formula, const std::vector<char32_t> variables)
{
	static constexpr const char32_t* NotSymbol = U"\u00AC";
	static constexpr const char32_t* AndSymbol = U"AND";
	static constexpr const char32_t* OrSymbol = U"OR";

	const unsigned int solutionCount = std::pow(2, variables.size());
	std::optional<std::bitset<32>> solution;

	for (unsigned int i = 0; i < solutionCount; ++i)
	{
		const std::bitset<32> binarySolution(i);
		std::u32string newFormula = formula;

		for (size_t i = 0; i < variables.size(); ++i)
		{
			const std::u32string currentValue = binarySolution.test(i) ? U"true" : U"false";
			newFormula = ReplaceAll(newFormula, std::u32string(1, variables[i]), currentValue);
			newFormula = ReplaceAll(newFormula, NotSymbol, U"!");
			newFormula = ReplaceAll(newFormula, AndSymbol, U"&&");
			newFormula = ReplaceAll(newFormula, OrSymbol, U"||");
		}

		const std::string flattenedFormula(std::cbegin(newFormula), std::cend(newFormula));

		// MathExpr from https://github.com/k3a/MathExpr
		if (MathExpr expression;
			expression.eval(flattenedFormula.c_str()).isNumber() > 0.0)
		{
			solution = binarySolution;

			break;
		}
	}

	if (!solution.has_value())
	{
		return std::nullopt;
	}

	std::unordered_map<char32_t, bool> variableSolutions;

	for (size_t i = 0; i < variables.size(); ++i)
	{
		variableSolutions[variables[i]] = solution.value().test(i);
	}

	return variableSolutions;
}

std::ostream& operator <<(std::ostream& outputStream, const std::unordered_map<char32_t, bool>& variableMap)
{
	outputStream << std::boolalpha;

	for (const auto [variable, value] : variableMap)
	{
		outputStream << variable << ": " << value << "\n";
	}

	return outputStream;
}

int main(const int argc, const char* const argv[])
{
	std::cout << SatisfyBooleanFormula(U"(\u00ACc OR b) AND (b OR c) AND (\u00ACb OR c) AND (\u00ACc OR \u00ACa)", { U'a', U'b', U'c' }).value() << "\n";

	std::cin.get();

	return EXIT_SUCCESS;
}