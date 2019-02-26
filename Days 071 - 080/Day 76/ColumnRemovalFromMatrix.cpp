#include <iostream>
#include <vector>

unsigned int GetColumnRemovalCount(const std::vector<std::vector<char>>& matrix) noexcept
{
	if (matrix.empty())
	{
		return 0;
	}

	unsigned int rows = matrix.size();

	if (rows == 1)
	{
		return 0;
	}

	unsigned int columns = matrix[0].size();
	unsigned int columnRemovalCount = 0;
	
	for (unsigned int i = 0; i < columns; i++)
	{
		for (unsigned int j = 1; j < rows; j++)
		{
			if (matrix[j - 1][i] > matrix[j][i])
			{
				columnRemovalCount++;

				break;
			}
		}
	}

	return columnRemovalCount;
}

int main(int argc, char* argv[])
{
	std::cout << GetColumnRemovalCount({ { 'c', 'b', 'a' }, { 'd', 'a', 'f' }, { 'g', 'h', 'i' } }) << "\n";
	std::cout << GetColumnRemovalCount({ {'a', 'b', 'c', 'd', 'e', 'f' } }) << "\n";
	std::cout << GetColumnRemovalCount({ { 'z', 'y', 'x' }, { 'w', 'v', 'u' }, { 't', 's', 'r' } }) << "\n";

	std::cin.get();

	return 0;
}