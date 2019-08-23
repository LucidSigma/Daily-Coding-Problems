#include <cstddef>
#include <cstdlib>
#include <iostream>
#include <string>

enum Orientation
	: char
{
	Left = 'L',
	Right = 'R',
	Still = '.'
};

std::string GetDominoOrientationHelper(std::string& dominoes)
{
	unsigned int changeCount = 0;

	for (size_t i = 0; i < dominoes.length(); ++i)
	{
		if (dominoes[i] == Orientation::Left && i > 0 && dominoes[i - 1] == Orientation::Still)
		{
			if (i - 2 > 0 || (i - 2 <= 0 && dominoes[i - 2] != Orientation::Right))
			{
				dominoes[i - 1] = Orientation::Left;
				++changeCount;
			}
		}
		else if (dominoes[i] == Orientation::Right && i < dominoes.length() && dominoes[i + 1] == Orientation::Still)
		{
			if (i + 2 <= dominoes.length() || (i + 2 > dominoes.length() && dominoes[i + 2] != Orientation::Left))
			{
				dominoes[i + 1] = Orientation::Right;
				++changeCount;
			}
		}
	}

	return changeCount > 0 ? GetDominoOrientationHelper(dominoes) : dominoes;
}

inline std::string GetDominoOrientation(std::string dominoes)
{
	return GetDominoOrientationHelper(dominoes);
}

int main(int argc, char* argv[])
{
	std::cout << GetDominoOrientation(".L.R....L") << "\n";
	std::cout << GetDominoOrientation("..R...L.L") << "\n";

	std::cin.get();

	return EXIT_SUCCESS;
}