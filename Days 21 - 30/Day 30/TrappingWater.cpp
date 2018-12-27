#include <array>
#include <iostream>

template <unsigned int Size>
unsigned int CalculateTrappedWater(const std::array<unsigned int, Size>& heights) noexcept
{
	unsigned int totalTrappedWater = 0;

	unsigned int currentPoolLeft = 0;
	unsigned int currentPoolRight = 0;

	int lowIndex = 0;
	int highIndex = Size - 1;

	while (lowIndex <= highIndex)
	{
		if (heights[lowIndex] < heights[highIndex])
		{
			if (heights[lowIndex] > currentPoolLeft)
			{
				currentPoolLeft = heights[lowIndex];
			}
			else
			{
				totalTrappedWater += currentPoolLeft - heights[lowIndex];
				lowIndex++;
			}
		}
		else
		{
			if (heights[highIndex] > currentPoolRight)
			{
				currentPoolRight = heights[highIndex];
			}
			else
			{
				totalTrappedWater += currentPoolRight - heights[highIndex];
				highIndex--;
			}
		}
	}

	return totalTrappedWater;
}

int main(int argc, const char* argv[])
{
	std::cout << CalculateTrappedWater<3>({ 2, 1, 2 }) << "\n";
	std::cout << CalculateTrappedWater<6>({ 3, 0, 1, 3, 0, 5 }) << "\n";

	std::cin.get();

	return 0;
}