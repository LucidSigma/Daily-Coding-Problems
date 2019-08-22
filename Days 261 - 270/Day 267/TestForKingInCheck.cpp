#include <array>
#include <cmath>
#include <cstddef>
#include <cstdlib>
#include <iostream>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

static constexpr size_t BoardSize = 8u;

enum class PieceType
	: char
{
	King = 'K',
	Queen = 'Q',
	Rook = 'R',
	Bishop = 'B',
	Knight = 'N',
	Pawn = 'P'
};

using Coordinate = std::pair<size_t, size_t>;

struct Piece
{
	PieceType type;
	Coordinate coordinate;
};

class Board
{
private:
	std::array<std::string, BoardSize> m_board;
	std::vector<Piece> m_pieces;
	Piece m_king{ };

	const std::unordered_map<PieceType, bool (Board::*)(const Coordinate&) const> m_attackFunctionLookup
	{
		{ PieceType::Queen, &Board::AttackedByQueen },
		{ PieceType::Rook, &Board::AttackedByRook },
		{ PieceType::Bishop, &Board::AttackedByBishop },
		{ PieceType::Knight, &Board::AttackedByKnight },
		{ PieceType::Pawn, &Board::AttackedByPawn }
	};

public:
	Board(const std::array<std::string, BoardSize>& board)
		: m_board(board)
	{
		for (size_t i = 0; i < m_board.size(); ++i)
		{
			for (size_t j = 0; j < m_board[i].length(); ++j)
			{
				if (m_board[i][j] == '.')
				{
					continue;
				}

				const Piece currentPiece{ static_cast<PieceType>(m_board[i][j]), { i, j } };
				
				if (currentPiece.type == PieceType::King)
				{
					m_king = currentPiece;
				}
				else
				{
					m_pieces.push_back(currentPiece);
				}
			}
		}
	}

	bool IsKingInCheck() const
	{
		for (const auto& piece : m_pieces)
		{
			if ((this->*(m_attackFunctionLookup.at(piece.type)))(piece.coordinate))
			{
				return true;
			}
		}

		return false;
	}

private:
	inline Coordinate GetKingDeltaCoordinates(const Coordinate& coordinate) const
	{
		return
		{
			static_cast<size_t>(std::abs(static_cast<int>(coordinate.first) - static_cast<int>(m_king.coordinate.first))),
			static_cast<size_t>(std::abs(static_cast<int>(coordinate.second) - static_cast<int>(m_king.coordinate.second)))
		};
	}

	inline bool AttackedByQueen(const Coordinate& coordinate) const
	{
		return AttackedByRook(coordinate) || AttackedByBishop(coordinate);
	}

	inline bool AttackedByRook(const Coordinate& coordinate) const
	{
		return coordinate.first == m_king.coordinate.first || coordinate.second == m_king.coordinate.second;
	}

	inline bool AttackedByBishop(const Coordinate& coordinate) const
	{
		const auto [deltaX, deltaY] = GetKingDeltaCoordinates(coordinate);

		return deltaX == deltaY;
	}

	inline bool AttackedByKnight(const Coordinate& coordinate) const
	{
		const auto [deltaX, deltaY] = GetKingDeltaCoordinates(coordinate);

		return deltaX * deltaY == 2;
	}

	inline bool AttackedByPawn(const Coordinate& coordinate) const
	{ 
		return (coordinate.second == m_king.coordinate.first - 1 || coordinate.second == m_king.coordinate.first + 1) &&
			   coordinate.first == m_king.coordinate.first + 1;
	}
};

int main(int argc, char* argv[])
{
	const std::array<std::string, BoardSize> pieces
	{
		"...K....",
		"........",
		".B......",
		"......P.",
		".......R",
		"..N.....",
		"........",
		".....Q.."
	};

	const Board board(pieces);

	std::cout << std::boolalpha;
	std::cout << board.IsKingInCheck() << "\n";

	std::cin.get();

	return EXIT_SUCCESS;
}