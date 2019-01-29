#include <iostream>

unsigned int TotalMatrixTraversalsHelper(unsigned int rows, unsigned int columns, unsigned int currentRow, unsigned int currentColumn) noexcept
{
	if (currentRow == rows - 1 && currentColumn == columns - 1)
	{
		return 1;
	}

	unsigned int traversals = 0;

	if (currentRow < rows - 1)
	{
		traversals += TotalMatrixTraversalsHelper(rows, columns, currentRow + 1, currentColumn);
	}

	if (currentColumn < columns - 1)
	{
		traversals += TotalMatrixTraversalsHelper(rows, columns, currentRow, currentColumn + 1);
	}

	return traversals;
}

unsigned int TotalMatrixTraversals(unsigned int rows, unsigned int columns) noexcept
{
	if (rows == 0 || columns == 0)
	{
		return 0;
	}

	return TotalMatrixTraversalsHelper(rows, columns, 0, 0);;
}

int main(int argc, char* argv[])
{
	std::cout << TotalMatrixTraversals(2, 2) << "\n";
	std::cout << TotalMatrixTraversals(5, 5) << "\n";

	std::cin.get();

	return 0;
}
