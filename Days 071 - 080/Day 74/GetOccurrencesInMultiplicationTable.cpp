#include <iostream>

unsigned int GetOccurrencesInMultiplicationTable(const unsigned int n, const unsigned int x) noexcept
{
	unsigned int occurrenceCount = 0;

	for (unsigned int i = 1; i <= n; i++)
	{
		if (x % i == 0 && x / i <= n)
		{
			occurrenceCount++;
		}
	}

	return occurrenceCount;
}

int main(int argc, char* argv[])
{
	std::cout << GetOccurrencesInMultiplicationTable(6, 12) << "\n";

	std::cin.get();

	return 0;
}