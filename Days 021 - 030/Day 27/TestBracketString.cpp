#include <iostream>
#include <stack>
#include <string>

bool HasValidBrackets(const std::string& string) noexcept
{
	static constexpr unsigned int BRACKET_TYPE_COUNT = 4;

	static constexpr char BRACKETS[BRACKET_TYPE_COUNT][2]
	{
		{ '(', ')' },
		{ '[', ']' },
		{ '{', '}' },
		{ '<', '>' }
	};

	static enum State : unsigned int { Open, Closed };
	static enum Type : unsigned int { Parenthesis, Square, Brace, Chevron, Undefined };

	static constexpr auto isBracket = [](char bracket, State state) noexcept -> bool
	{
		for (unsigned int i = 0; i < BRACKET_TYPE_COUNT; i++)
		{
			if (bracket == BRACKETS[i][state])
			{
				return true;
			}
		}

		return false;
	};

	static constexpr auto bracketType = [](char bracket) noexcept -> Type
	{
		for (unsigned int i = 0; i < BRACKET_TYPE_COUNT; i++)
		{
			if ((bracket == BRACKETS[i][Open]) || (bracket == BRACKETS[i][Closed]))
			{
				return static_cast<Type>(i);
			}
		}

		return Undefined;
	};

	std::stack<char> bracketStack;

	for (const char letter : string)
	{
		if (isBracket(letter, Open))
		{
			bracketStack.push(letter);
		}
		else if (isBracket(letter, Closed))
		{
			if (bracketStack.top() == BRACKETS[bracketType(letter)][Open])
			{
				bracketStack.pop();
			}
			else
			{
				return false;
			}
		}
	}

	return bracketStack.empty();
}

int main(int argc, const char* argv[])
{
	std::cout << std::boolalpha;

	std::cout << HasValidBrackets("([])[]({})") << "\n";
	std::cout << HasValidBrackets("([)]") << "\n";
	std::cout << HasValidBrackets("((()") << "\n";
	std::cout << HasValidBrackets("s(sd[g35{4mj6m,j5l<46k>5kik65mkili}7]uu7gd)78fsdf") << "\n";
	
	std::cin.get();

	return 0;
}
