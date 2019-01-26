#include <algorithm>
#include <chrono>
#include <fstream>
#include <iostream>
#include <limits>
#include <stdexcept>
#include <string>
#include <thread>
#include <vector>

enum class CellStates : char
{
	Alive = '*',
	Dead = '.'
};

struct Cell
{
	static int minX;
	static int maxX;
	static int minY;
	static int maxY;

	int x;
	int y;

	explicit Cell(int x, int y) noexcept
		: x(x), y(y)
	{ }

	friend bool operator <(const Cell& lhs, const Cell& rhs) noexcept;
	friend bool operator ==(const Cell& lhs, const Cell& rhs) noexcept;
};

int Cell::minX = std::numeric_limits<int>::max();
int Cell::maxX = std::numeric_limits<int>::min();
int Cell::minY = std::numeric_limits<int>::max();
int Cell::maxY = std::numeric_limits<int>::min();

bool operator <(const Cell& lhs, const Cell& rhs) noexcept
{
	return lhs.x != rhs.x ? lhs.x < rhs.x : lhs.y < rhs.y;
}

bool operator ==(const Cell& lhs, const Cell& rhs) noexcept
{
	return (lhs.x == rhs.x) && (lhs.y == rhs.y);
}

void PrintBoard(const std::vector<std::string>& board, unsigned int iteration = 0)
{
	static const std::string ScreenClearer(100, '\n');

	std::cout << ScreenClearer;
	std::cout << "Iteration " << iteration << "\n";

	for (const auto& row : board)
	{
		std::cout << row << "\n";
	}
}

unsigned int GetNeighbourCount(const std::vector<std::string>& board, unsigned int x, unsigned int y) noexcept
{
	unsigned int count = 0;

	for (unsigned int i = x - 1; i <= static_cast<int>(x + 1); i++)
	{
		for (unsigned int j = y - 1; j <= static_cast<int>(y + 1); j++)
		{
			if (i >= 0 && i < static_cast<int>(board.size()) &&
				j >= 0 && j < static_cast<int>(board[i].length()) &&
				!(i == x && j == y) && board[i][j] == static_cast<char>(CellStates::Alive))
			{
				count++;
			}
		}
	}

	return count;
}

void UpdateCellMinAndMax(const std::vector<Cell>& cells) noexcept
{
	Cell::minX = std::numeric_limits<int>::max();
	Cell::maxX = std::numeric_limits<int>::min();
	Cell::minY = std::numeric_limits<int>::max();
	Cell::maxY = std::numeric_limits<int>::min();

	for (const auto& cell : cells)
	{
		Cell::minX = std::min(cell.x, Cell::minX);
		Cell::maxX = std::max(cell.x, Cell::maxX);
		Cell::minY = std::min(cell.y, Cell::minY);
		Cell::maxY = std::max(cell.y, Cell::maxY);
	}

	Cell::minX--;
	Cell::maxX++;
	Cell::minY--;
	Cell::maxY++;
}

std::vector<std::string> CellsToBoard(const std::vector<Cell>& cells) noexcept
{
	std::vector<std::string> board;

	for (int i = 0; i < (Cell::maxX - Cell::minX + 1); i++)
	{
		board.emplace_back(Cell::maxY - Cell::minY + 1, static_cast<char>(CellStates::Dead));
	}

	for (const auto& cell : cells)
	{
		board[cell.x - Cell::minX][cell.y - Cell::minY] = static_cast<char>(CellStates::Alive);
	}

	return board;
}

std::vector<Cell> CreateCellsFromBoard(const std::vector<std::string>& board) noexcept
{
	std::vector<Cell> cells;

	for (unsigned int i = 0; i < board.size(); i++)
	{
		for (unsigned int j = 0; j < board[i].length(); j++)
		{
			if (board[i][j] == static_cast<char>(CellStates::Alive))
			{
				cells.emplace_back(i, j);
			}
		}
	}

	return cells;
}

std::vector<std::string> IterateCells(std::vector<Cell>& cells)
{
	UpdateCellMinAndMax(cells);

	std::vector<std::string> board;

	std::vector<Cell> newCells;
	std::vector<Cell> deadCells;

	if (!cells.empty())
	{
		board = CellsToBoard(cells);

		for (unsigned int i = 1; i < board.size() - 1; i++)
		{
			for (unsigned int j = 1; j < board[i].length() - 1; j++)
			{
				if (board[i][j] == static_cast<char>(CellStates::Alive))
				{
					unsigned int neighbourCount = GetNeighbourCount(board, i, j);

					if (constexpr unsigned int POPULATION_MIN = 2, POPULATION_MAX = 3; (neighbourCount < POPULATION_MIN) || (neighbourCount > POPULATION_MAX))
					{
						deadCells.emplace_back(i, j);
					}
				}
			}
		}

		for (unsigned int i = 0; i < board.size(); i++)
		{
			for (unsigned int j = 0; j < board[i].length(); j++)
			{
				if (board[i][j] == static_cast<char>(CellStates::Dead))
				{
					unsigned int neighbourCount = GetNeighbourCount(board, i, j);

					if (constexpr unsigned int REBIRTH_COUNT = 3; neighbourCount == REBIRTH_COUNT)
					{
						newCells.emplace_back(i, j);
					}
				}
			}
		}

		for (const auto& cell : newCells)
		{
			board[cell.x][cell.y] = static_cast<char>(CellStates::Alive);
		}

		for (const auto& cell : deadCells)
		{
			board[cell.x][cell.y] = static_cast<char>(CellStates::Dead);
		}

		cells = CreateCellsFromBoard(board);
	}
	else
	{
		board.emplace_back(1, static_cast<char>(CellStates::Dead));
	}

	return board;
}

void GameOfLife(const std::vector<Cell>& cells, unsigned int iterations = 100, unsigned int millisecondDelta = 500)
{
	UpdateCellMinAndMax(cells);
	std::vector<std::string> board = CellsToBoard(cells);

	PrintBoard(board);
	std::this_thread::sleep_for(std::chrono::milliseconds(millisecondDelta));

	std::vector<Cell> changingCells = cells;

	for (unsigned int i = 0; i < iterations; i++)
	{
		board = IterateCells(changingCells);
		PrintBoard(board, i + 1);

		std::this_thread::sleep_for(std::chrono::milliseconds(millisecondDelta));
	}
}

std::vector<Cell> GetCellsFromFile(const std::string& filename)
{
	std::ifstream cellFile(filename);

	if (!cellFile.is_open())
	{
		throw std::invalid_argument("File " + filename + " could not be found/opened.");
	}

	std::vector<Cell> cells;

	std::string currentLine;
	unsigned int lineCounter = 0;

	while (std::getline(cellFile, currentLine))
	{
		for (unsigned int i = 0; i < currentLine.length(); i++)
		{
			if (currentLine[i] == static_cast<char>(CellStates::Alive))
			{
				cells.emplace_back(lineCounter, i);
			}
		}

		lineCounter++;
	}

	return cells;
}

int main(int argc, const char* argv[])
{
	auto cells = GetCellsFromFile("Board.txt");
	GameOfLife(cells);

	std::cin.get();

	return 0;
}
