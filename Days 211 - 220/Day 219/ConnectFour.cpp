#include <algorithm>
#include <array>
#include <cstddef>
#include <cstdlib>
#include <iostream>
#include <iterator>

class ConnectFour
{
private:
	static constexpr size_t s_BoardWidth = 7u;
	static constexpr size_t s_BoardHeight = 6u;
	static constexpr size_t s_WinLength = 4u;

	enum class Player
		: char
	{
		None = ' ',
		One = 'O',
		Two = 'X'
	};

	template <size_t W, size_t H>
	using Board = std::array<std::array<Player, W>, H>;

	Board<s_BoardWidth, s_BoardHeight> m_board{ };
	Player m_currentPlayer = Player::One;

	bool m_isRunning = true;
	bool m_isDraw = false;

public:
	ConnectFour() noexcept
	{
		for (auto& row : m_board)
		{
			std::fill(std::begin(row), std::end(row), Player::None);
		}
	};

	~ConnectFour() noexcept = default;

	void Play() noexcept
	{
		while (m_isRunning)
		{
			PlacePiece(GetPlayerColumnChoice());

			if (CheckWin())
			{
				m_isRunning = false;
			}
			else if (CheckDraw())
			{
				m_isDraw = true;
				m_isRunning = false;
			}
			else
			{
				SwapPlayers();
			}
		}

		AnnounceResult();
	}

private:
	size_t GetPlayerColumnChoice() const noexcept
	{
		ClearScreen();
		std::cout << m_board << "It is " << m_currentPlayer << "'s turn.\n";
		
		bool validChoice = false;
		size_t chosenColumn = 0;

		do
		{
			std::cout << "Enter the column of choice (0 - " << (s_BoardWidth - 1) << "): ";
			std::cin >> chosenColumn;

			if (std::cin.fail())
			{
				std::cout << "Invalid input, please try again.\n";
			}
			else if (chosenColumn >= s_BoardWidth)
			{
				std::cout << "Invalid column, please try again.\n";
			}
			else if (IsColumnFull(chosenColumn))
			{
				std::cout << "Column is full, please try again.\n";
			}
			else
			{
				validChoice = true;
			}

			std::cin.clear();
			std::cin.ignore(10'000, '\n');
		}
		while (!validChoice);

		return chosenColumn;
	}

	void PlacePiece(const size_t column) noexcept
	{
		for (size_t i = 0; i < s_BoardHeight; ++i)
		{
			if (m_board[i][column] == Player::None)
			{
				m_board[i][column] = m_currentPlayer;

				return;
			}
		}
	}

	bool CheckWin() const noexcept
	{
		for (size_t y = 0; y < s_WinLength; ++y)
		{
			for (size_t x = 0; x < s_WinLength; ++x)
			{
				if (m_board[y][x] == m_currentPlayer &&
					m_board[y + 1][x] == m_currentPlayer &&
					m_board[y + 2][x] == m_currentPlayer &&
					m_board[y + 3][x] == m_currentPlayer)
				{
					return true;
				}

				if (m_board[y][x] == m_currentPlayer &&
					m_board[y][x + 1] == m_currentPlayer &&
					m_board[y][x + 2] == m_currentPlayer &&
					m_board[y][x + 3] == m_currentPlayer)
				{
					return true;
				}

				if (m_board[y][x] == m_currentPlayer &&
					m_board[y + 1][x + 1] == m_currentPlayer &&
					m_board[y + 2][x + 2] == m_currentPlayer &&
					m_board[y + 3][x + 3] == m_currentPlayer)
				{
					return true;
				}

				if (m_board[y][x + 3] == m_currentPlayer &&
					m_board[y + 1][x + 2] == m_currentPlayer &&
					m_board[y + 2][x + 1] == m_currentPlayer &&
					m_board[y + 3][x] == m_currentPlayer)
				{
					return true;
				}
			}
		}

		return false;
	}

	bool CheckDraw() const noexcept
	{
		for (const auto& row : m_board)
		{
			for (const auto cell : row)
			{
				if (cell == Player::None)
				{
					return false;
				}
			}
		}

		return true;
	}

	inline void SwapPlayers() noexcept
	{
		m_currentPlayer = m_currentPlayer == Player::One ? Player::Two : Player::One;
	}

	void AnnounceResult() const noexcept
	{
		ClearScreen();
		std::cout << m_board << "\n";

		if (m_isDraw)
		{
			std::cout << "The game was a draw!\n";
		}
		else
		{
			std::cout << m_currentPlayer << " has won!\n";
		}
	}

	bool IsColumnFull(const size_t column) const noexcept
	{
		for (int i = s_BoardHeight - 1; i >= 0; --i)
		{
			if (m_board[i][column] == Player::None)
			{
				return false;
			}
		}

		return true;
	}

	inline void ClearScreen() const noexcept
	{
		static const std::string clearString(100, '\n');

		std::cout << clearString;
	}

	inline friend std::ostream& operator <<(std::ostream& outputStream, const Player player) noexcept
	{
		outputStream << static_cast<char>(player);

		return outputStream;
	}

	template <size_t W, size_t H>
	friend std::ostream& operator <<(std::ostream& outputStream, const Board<W, H>& board) noexcept
	{
		for (auto it = std::crbegin(board); it != std::crend(board); ++it)
		{
			for (const auto cell : *it)
			{
				outputStream << cell << " ";
			}

			outputStream << "\n";
		}

		return outputStream;
	}
};

int main(int argc, char* argv[])
{
	ConnectFour game;
	game.Play();

	std::cin.get();

	return EXIT_SUCCESS;
}