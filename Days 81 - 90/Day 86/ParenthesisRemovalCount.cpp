#include <iostream>
#include <string>

unsigned int ParenthesisRemovalCount(const std::string& parentheses) noexcept
{
	static constexpr char OpenBracket = '(';
	static constexpr char ClosedBracket = ')';

	unsigned int unmatchedOpenCount = 0;
	unsigned int unmatchedClosedCount = 0;

	for (const char parenthesis : parentheses)
	{
		switch (parenthesis)
		{
		case OpenBracket:
			unmatchedOpenCount++;

			break;

		case ClosedBracket:
			if (unmatchedOpenCount > 0)
			{
				unmatchedOpenCount--;
			}
			else
			{
				unmatchedClosedCount++;
			}

			break;

		default:
			break;
		}
	}

	return unmatchedClosedCount + unmatchedOpenCount;
}

int main(int argc, char* argv[])
{
	std::cout << ParenthesisRemovalCount("()()") << "\n";
	std::cout << ParenthesisRemovalCount("()())()") << "\n";
	std::cout << ParenthesisRemovalCount(")(") << "\n";
	std::cout << ParenthesisRemovalCount(")))((()))(((") << "\n";

	std::cin.get();

	return 0;
}