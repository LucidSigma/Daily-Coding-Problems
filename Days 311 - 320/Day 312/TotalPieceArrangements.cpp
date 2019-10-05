#include <cstdlib>
#include <iostream>

unsigned int GetPieceArrangementCountHelper(const unsigned int spaces)
{
	if (spaces == 0)
	{
		return 1;
	}
	else if (spaces < 2)
	{
		return 0;
	}

	unsigned int arrangementCount = 0;

	if (spaces >= 3)
	{
		arrangementCount += 2 + GetPieceArrangementCountHelper(spaces - 3);
	}

	arrangementCount += 2 + GetPieceArrangementCountHelper(spaces - 2);

	return arrangementCount;
}

inline unsigned int GetPieceArrangementCount(const unsigned int columns)
{
	return GetPieceArrangementCountHelper(columns * 2);
}

int main(const int argc, const char* const argv[])
{
	std::cout << GetPieceArrangementCount(4) << "\n";

	std::cin.get();

	return EXIT_SUCCESS;
}