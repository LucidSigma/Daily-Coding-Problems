using System;
using System.Collections.Generic;
using System.Linq;

namespace DailyCodingProblem
{
	internal class Day64
	{
		private const int UnvisitedSquare = -1;
		private const int PossibleKnightMoves = 8;

		private static int Main(string[] args)
		{
			Console.WriteLine(KnightsTour(5));

			Console.ReadLine();

			return 0;
		}

		private static int KnightsTour(int size)
		{
			int count = 0;

			for (int i = 0; i < size; i++)
			{
				for (int j = 0; j < size; j++)
				{
					int[,] board = new int[size, size];

					for (int row = 0; row < size; row++)
					{
						for (int column = 0; column < size; column++)
						{
							board[row, column] = UnvisitedSquare;
						}
					}

					board[i, j] = 0;
					List<(int, int)> tour = new List<(int, int)> { (i, j) };

					count += KnightsTourHelper(board, tour);
				}
			}

			return count;
		}

		private static int KnightsTourHelper(int[,] board, List<(int, int)> tour)
		{
			if (tour.Count == board.GetLength(0) * board.GetLength(1))
			{
				return 1;
			}

			int count = 0;
			(int lastX, int lastY) = tour[tour.Count - 1];

			foreach ((int x, int y) in GetValidMoves(board, lastX, lastY))
			{
				tour.Add((x, y));
				board[x, y] = tour.Count;

				count += KnightsTourHelper(board, tour);

				tour.RemoveAt(tour.Count - 1);
				board[x, y] = UnvisitedSquare;
			}

			return count;
		}

		private static List<(int, int)> GetValidMoves(int[,] board, int x, int y)
		{
			(int, int)[] moveDeltas = new (int, int)[]
			{
				(2, 1),
				(1, 2),
				(1, -2),
				(-2, 1),
				(-1, 2),
				(2, -1),
				(-1, -2),
				(-2, -1)
			};

			var possibleMoves = from moveDelta in moveDeltas
								let move = (x + moveDelta.Item1, y + moveDelta.Item2)
								where IsValidMove(board, move.Item1, move.Item2)
								select move;

			return possibleMoves.ToList();
		}

		private static bool IsValidMove(int[,] board, int x, int y) => x >= 0 && x < board.GetLength(0) && y >= 0 && y < board.GetLength(1) && board[x, y] == UnvisitedSquare;
	}
}