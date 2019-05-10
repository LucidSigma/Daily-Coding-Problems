#include <functional>
#include <initializer_list>
#include <iostream>
#include <stack>
#include <string>
#include <unordered_map>
#include <variant>

int EvaluateReversePolishNotation(const std::initializer_list<std::variant<int, std::string>>& tokens) noexcept
{
	std::stack<int> numberStack;

	for (const auto& token : tokens)
	{
		if (std::holds_alternative<int>(token))
		{
			numberStack.push(std::get<int>(token));
		}
		else
		{
			static const std::unordered_map<std::string, std::function<int(int, int)>> operatorFunctionLookup
			{
				{ "+", std::plus<int>() },
				{ "-", std::minus<int>() },
				{ "*", std::multiplies<int>() },
				{ "/", std::divides<int>() }
			};

			const int rhs = numberStack.top();
			numberStack.pop();

			const int lhs = numberStack.top();
			numberStack.pop();

			const auto currentFunction = operatorFunctionLookup.at(std::get<std::string>(token));

			numberStack.push(currentFunction(lhs, rhs));
		}
	}

	return numberStack.top();
}

int main(int argc, char* argv[])
{
	std::cout << EvaluateReversePolishNotation({ 5, 3, "+" }) << "\n";
	std::cout << EvaluateReversePolishNotation({ 15, 7, 1, 1, "+", "-", "/", 3, "*", 2, 1, 1, "+", "+", "-" }) << "\n";

	std::cin.get();

	return 0;
}