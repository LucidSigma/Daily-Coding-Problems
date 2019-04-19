#include <iostream>
#include <string>

bool AreBracketsBalanced(const std::string& bracketString) noexcept
{
	static constexpr char OpenBracket = '(';
	static constexpr char ClosedBracket = ')';
	static constexpr char Wildcard = '*';

	unsigned int openCount = 0;
	unsigned int wildcardCount = 0;

	for (const char character : bracketString)
	{
		switch (character)
		{
		case OpenBracket:
			openCount++;

			break;

		case ClosedBracket:
			if (openCount == 0 && wildcardCount == 0)
			{
				return false;
			}
			else if (openCount == 0)
			{
				wildcardCount--;
			
			}
			else
			{
				openCount--;
			}

			break;

		case Wildcard:
			wildcardCount++;

			break;

		default:
			break;
		}
	}

	return wildcardCount >= openCount;
}

int main(int argc, char* argv[])
{
	std::cout << std::boolalpha;
	std::cout << AreBracketsBalanced("(()*") << "\n";
	std::cout << AreBracketsBalanced("(*)") << "\n";
	std::cout << AreBracketsBalanced(")*(") << "\n";
	std::cout << AreBracketsBalanced("*)") << "\n";

	std::cin.get();

	return 0;
}