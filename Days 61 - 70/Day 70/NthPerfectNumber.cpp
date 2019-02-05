#include <iostream>

constexpr unsigned int GetNthPerfectNumber(unsigned int n) noexcept
{
	return 9 * (n + (n / 10)) + 10;
}

int main(int argc, char* argv[])
{
	for (unsigned int i = 1; i <= 20; i++)
	{
		std::cout << GetNthPerfectNumber(i) << "\n";
	}

	std::cin.get();

	return 0;
}