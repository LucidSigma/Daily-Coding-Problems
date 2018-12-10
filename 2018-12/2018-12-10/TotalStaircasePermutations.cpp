#include <initializer_list>
#include <iostream>
#include <vector>

unsigned int GetStaircasePermutations(unsigned int stairCount, const std::initializer_list<unsigned int>& spacings)
{
	std::vector<unsigned int> sequence(stairCount + 1, 0);
	sequence[0] = 1;

	for (unsigned int i = 1; i < stairCount + 1; i++)
	{
		for (unsigned int space : spacings)
		{
			int difference = static_cast<int>(i) - static_cast<int>(space);

			if (difference > 0)
			{
				sequence[i] += sequence[difference];
			}

			if (i == space)
			{
				sequence[i]++;
			}
		}
	}

	return sequence[stairCount];
}

int main(int argc, char* argv[])
{
	std::cout << GetStaircasePermutations(21, { 1, 3, 5 }) << std::endl;

	std::cin.get();

	return 0;
}