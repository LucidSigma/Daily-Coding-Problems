#include <algorithm>
#include <array>
#include <cstddef>
#include <cstdlib>
#include <iostream>
#include <iterator>

enum class Colour
{
	White,
	Black
};

template <size_t N>
using Matrix = std::array<std::array<Colour, N>, N>;

template <size_t N>
bool IsSymmetric(const Matrix<N>& crossword)
{
	for (size_t i = 0; i < N; ++i)
	{
		for (size_t j = 0; j < N; ++j)
		{
			if ((crossword[i][j] == Colour::Black) != (crossword[N - i - 1][N - j - 1] == Colour::Black))
			{
				return false;
			}
		}
	}

	return true;
}

template <size_t N>
bool AreWordsLongEnough(const Matrix<N>& crossword)
{
	static constexpr unsigned int MinLength = 3u;

	for (size_t i = 0; i < N; ++i)
	{
		int lastOpenSqaure = -static_cast<int>(MinLength + 1);
		int lastBlockedSquare = -1;

		for (size_t j = 0; j < N; ++j)
		{
			if (crossword[i][j] == Colour::Black)
			{
				if (lastOpenSqaure == static_cast<int>(j) - 1 && static_cast<int>(j) - lastBlockedSquare <= static_cast<int>(MinLength + 1))
				{
					return false;
				}

				lastBlockedSquare = j;
			}
			else
			{
				lastOpenSqaure = j;
			}
		}
	}

	for (size_t i = 0; i < N; ++i)
	{
		int lastOpenSqaure = -static_cast<int>(MinLength + 1);
		int lastBlockedSquare = -1;

		for (size_t j = 0; j < N; ++j)
		{
			if (crossword[i][j] == Colour::Black)
			{
				if (lastOpenSqaure == static_cast<int>(i) - 1 && static_cast<int>(i) - lastBlockedSquare <= static_cast<int>(MinLength + 1))
				{
					return false;
				}

				lastBlockedSquare = i;
			}
			else
			{
				lastOpenSqaure = i;
			}
		}
	}

	return true;
}

template <size_t N>
inline bool IsValidCrossword(const Matrix<N>& crossword)
{
	return IsSymmetric(crossword) && AreWordsLongEnough(crossword);
}

int main(const int argc, const char* const argv[])
{
	const Matrix<4> crossword
	{
		std::array<Colour, 4>{ Colour::Black, Colour::White, Colour::White, Colour::White },
		std::array<Colour, 4>{ Colour::White, Colour::White, Colour::White, Colour::Black },
		std::array<Colour, 4>{ Colour::Black, Colour::White, Colour::White, Colour::White },
		std::array<Colour, 4>{ Colour::White, Colour::White, Colour::White, Colour::Black }
	};

	std::cout << std::boolalpha;
	std::cout << IsValidCrossword(crossword) << "\n";

	std::cin.get();

	return EXIT_SUCCESS;
}