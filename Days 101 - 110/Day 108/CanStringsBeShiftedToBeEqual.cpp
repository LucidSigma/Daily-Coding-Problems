#include <algorithm>
#include <iostream>
#include <iterator>
#include <string>

bool CanStringBecomeAnotherByShifting(const std::string& a, const std::string& b) noexcept
{
	if (a.length() != b.length())
	{
		return false;
	}

	std::string shiftedString = a;

	for (unsigned int i = 1; i < a.length() - 1; i++)
	{
		std::rotate(std::begin(shiftedString), std::begin(shiftedString) + 1, std::end(shiftedString));

		if (shiftedString == b)
		{
			return true;
		}
	}

	return false;
}

int main(int argc, char* argv[])
{
	std::cout << std::boolalpha;
	std::cout << CanStringBecomeAnotherByShifting("abcde", "cdeab") << "\n";
	std::cout << CanStringBecomeAnotherByShifting("abc", "acb") << "\n";

	std::cin.get();

	return 0;
}