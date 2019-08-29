#include <cstddef>
#include <cstdlib>
#include <functional>
#include <iostream>
#include <locale>
#include <stack>
#include <string>
#include <unordered_map>

void EvaluateSubexpression(std::stack<int>& values, std::stack<char>& operators)
{
	const int lhs = values.top();
	values.pop();

	const int rhs = values.top();
	values.pop();

	static const std::unordered_map<char, std::function<int(int, int)>> operatorLookup
	{
		{ '+', std::plus<int>() },
		{ '-', std::minus<int>() },
		{ '*', std::multiplies<int>() },
		{ '/', std::divides<int>() }
	};

	const int result = operatorLookup.at(operators.top())(lhs, rhs);
	operators.pop();

	values.push(result);
}

int EvaluateExpression(const std::string& expression)
{
	std::stack<int> values;
	std::stack<char> operators;

	bool isNegative = false;

	for (size_t i = 0; i < expression.length(); ++i)
	{
		if (expression[i] == ' ')
		{
			continue;
		}
		else if (expression[i] == '(')
		{
			operators.push(expression[i]);
		}
		else if (std::isdigit(expression[i], std::locale("")))
		{
			int value = 0;

			while (i < expression.length() && std::isdigit(expression[i], std::locale("")))
			{
				value *= 10;
				value += expression[i] - '0';

				++i;
			}

			if (isNegative)
			{
				value *= -1;
				isNegative = false;
			}

			values.push(value);
		}
		else if (expression[i] == ')')
		{
			while (!operators.empty() && operators.top() != '(')
			{
				EvaluateSubexpression(values, operators);
			}

			if (!operators.empty())
			{
				operators.pop();
			}
		}
		else
		{
			static constexpr auto precedence = [](const char operation) -> unsigned int
			{
				if (operation == '*' || operation == '/')
				{
					return 2;
				}
				else if (operation == '+' || operation == '-')
				{
					return 1;
				}
				else
				{
					return 0;
				}
			};

			if (expression[i] == '-' && expression[i + 1] != ' ')
			{
				isNegative = true;

				continue;
			}
			else if (expression[i] == '+' && expression[i + 1] != ' ')
			{
				continue;
			}
			else
			{
				while (!operators.empty() && precedence(operators.top()) >= precedence(expression[i]))
				{
					EvaluateSubexpression(values, operators);
				}

				operators.push(expression[i]);
			}
		}
	}

	while (!operators.empty())
	{
		EvaluateSubexpression(values, operators);
	}

	return values.top();
}

int main(int argc, char* argv[])
{
	std::cout << EvaluateExpression("-1 + (2 + 3)") << "\n";

	std::cin.get();

	return EXIT_SUCCESS;
}