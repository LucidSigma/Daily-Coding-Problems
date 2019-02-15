#include <array>
#include <iostream>

template <unsigned int Size>
bool CanBecomeIncreasingInOneChange(const std::array<int, Size>& numbers) noexcept
{
	bool requiresOneChange = false;

	for (unsigned int i = 0; i < Size - 1; i++)
	{
		if (numbers[i] > numbers[i + 1])
		{
			if (requiresOneChange)
			{
				return false;
			}

			requiresOneChange = true;
		}
	}

	return true;
}

int main(int argc, char* argv[])
{
	std::cout << std::boolalpha;
	std::cout << CanBecomeIncreasingInOneChange<3>({ 10, 5, 7 }) << "\n";
	std::cout << CanBecomeIncreasingInOneChange<3>({ 10, 5, 1 }) << "\n";

	std::cin.get();

	return 0;
}