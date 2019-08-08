#include <cstddef>
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>

std::string CreateZigzag(const std::string& string, const size_t k)
{
	std::vector<std::string> rows(k);
	size_t currentRow = 0;
	int direction = -1;

	for (const char letter : string)
	{
		for (size_t i = 0; i < rows.size(); ++i)
		{
			rows[i] += i == currentRow ? letter : ' ';
		}

		if (currentRow == k - 1 || currentRow == 0)
		{
			direction *= -1;
		}

		currentRow += direction;
	}

	std::string zigzagString;

	for (const auto& row : rows)
	{
		zigzagString += row + "\n";
	}

	return zigzagString;
}

int main(int argc, char* argv[])
{
	std::cout << CreateZigzag("thisisazigzag", 4) << "\n";

	std::cin.get();

	return EXIT_SUCCESS;
}