#include <array>
#include <iostream>
#include <string>

template <unsigned int Size>
bool ContainsWord(const std::array<std::array<char, Size>, Size>& matrix, const std::string& target)
{
	for (unsigned int i = 0; i < Size; i++)
	{
		std::string horizontal;

		for (const char letter : matrix[i])
		{
			horizontal += letter;
		}

		std::string vertical;

		for (unsigned int j = 0; j < Size; j++)
		{
			vertical += matrix[j][i];
		}

		if (horizontal == target || vertical == target)
		{
			return true;
		}
	}

	return false;
}

int main(int argc, char* argv[])
{
	const std::array<std::array<char, 4>, 4> matrix
	{
		std::array<char, 4> { 'F', 'A', 'C', 'I' },
		std::array<char, 4> { 'O', 'B', 'Q', 'P' },
		std::array<char, 4> { 'A', 'N', 'O', 'B' },
		std::array<char, 4> { 'M', 'A', 'S', 'S' },
	};

	std::cout << std::boolalpha;
	std::cout << ContainsWord(matrix, "FOAM") << "\n";
	std::cout << ContainsWord(matrix, "TEST") << "\n";
	std::cout << ContainsWord(matrix, "MASS") << "\n";

	std::cin.get();

	return 0;
}
