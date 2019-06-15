#include <cstddef>
#include <iostream>
#include <string>

std::string BalanceParentheses(const std::string& parentheses)
{
	using namespace std::literals::string_literals;

	static constexpr char OpenParenthesis = '(';
	static constexpr char ClosedParenthesis = ')';

	const std::size_t firstClosedParenthesisIndex = parentheses.find_first_of(ClosedParenthesis);

	if (firstClosedParenthesisIndex == std::string::npos)
	{
		return ""s;
	}

	const std::string tailParentheses = parentheses.substr(firstClosedParenthesisIndex);
	int openParenthesisCount = 0;

	for (std::size_t i = 0; i < tailParentheses.length(); ++i)
	{
		switch (tailParentheses[i])
		{
		case OpenParenthesis:
			++openParenthesisCount;

			break;

		case ClosedParenthesis:
			--openParenthesisCount;

			break;

		default:
			break;
		}

		if (openParenthesisCount == 0)
		{
			break;
		}
	}

	return openParenthesisCount > 0
		   ? tailParentheses.substr(openParenthesisCount)
		   : tailParentheses.substr(0, firstClosedParenthesisIndex) + BalanceParentheses(tailParentheses.substr(firstClosedParenthesisIndex + 1));
}

int main(int argc, char* argv[])
{
	std::cout << BalanceParentheses("(()") << "\n";
	std::cout << BalanceParentheses("))()(") << "\n";

	std::cin.get();

	return 0;
}