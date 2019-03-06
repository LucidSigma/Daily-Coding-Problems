#include <array>
#include <cstddef>
#include <iostream>
#include <iterator>
#include <string>
#include <unordered_set>

struct Point
{
	unsigned int x;
	unsigned int y;
};

inline bool operator ==(const Point& lhs, const Point& rhs) noexcept
{
	return lhs.x == rhs.x && lhs.y == rhs.y;
}

template<>
struct std::hash<Point>
{
	std::size_t operator ()(const Point& point) const noexcept
	{
		return std::hash<unsigned int>()(point.x) + std::hash<unsigned int>()(point.y);
	}
};

template <unsigned int M, unsigned int N>
bool IsWordInBoardHelper(const std::string& word, const std::array<std::array<char, M>, N>& board, unsigned int row, unsigned int column, const std::unordered_set<Point>& visitedPoints) noexcept
{
	if (word.empty())
	{
		return true;
	}

	bool topLetter = false;
	bool bottomLetter = false;
	bool leftLetter = false;
	bool rightLetter = false;

	if (row > 0)
	{
		topLetter = IsCorrectLetter(word, board, row - 1, column, visitedPoints);
	}

	if (row < board.size() - 1)
	{
		bottomLetter = IsCorrectLetter(word, board, row + 1, column, visitedPoints);
	}

	if (column > 0)
	{
		leftLetter = IsCorrectLetter(word, board, row, column - 1, visitedPoints);
	}

	if (column < board[0].size() - 1)
	{
		rightLetter = IsCorrectLetter(word, board, row , column + 1, visitedPoints);
	}

	return topLetter || bottomLetter || leftLetter || rightLetter;
}

template <unsigned int M, unsigned int N>
bool IsCorrectLetter(const std::string& word, const std::array<std::array<char, M>, N>& board, unsigned int row, unsigned int column, const std::unordered_set<Point>& visitedPoints) noexcept
{
	const char currentLetter = word[0];
	const char boardLetter = board[row][column];

	std::unordered_set<Point> currentVisitedPoints = visitedPoints;

	bool result = false;

	if (currentLetter == boardLetter && currentVisitedPoints.find({ row, column }) == std::cend(currentVisitedPoints))
	{
		currentVisitedPoints.insert({ row, column });

		result = IsWordInBoardHelper(word.substr(1), board, row, column, currentVisitedPoints);
	}

	return result;
}

template <unsigned int M, unsigned int N>
bool IsWordInBoard(const std::string& word, const std::array<std::array<char, M>, N>& board) noexcept
{
	if (word.empty())
	{
		return false;
	}

	const char firstLetter = word[0];
	bool isInBoard = false;

	for (unsigned int y = 0; y < board.size(); y++)
	{
		for (unsigned int x = 0; x < board[y].size(); x++)
		{
			if (board[y][x] == firstLetter)
			{
				isInBoard = IsWordInBoardHelper(word.substr(1), board, y, x, { { x, y } });
			}
		}
	}

	return isInBoard;
}

int main(int argc, char* argv[])
{
	const std::array<std::array<char, 4>, 3> letterBoard
	{
		std::array<char, 4> { 'A', 'B', 'C', 'E' },
		std::array<char, 4> { 'S', 'F', 'C', 'S' },
		std::array<char, 4> { 'A', 'D', 'E', 'E' }
	};

	std::cout << std::boolalpha;
	std::cout << IsWordInBoard("ABCCED", letterBoard) << "\n";
	std::cout << IsWordInBoard("SEE", letterBoard) << "\n";
	std::cout << IsWordInBoard("ABCB", letterBoard) << "\n";

	std::cin.get();

	return 0;
}