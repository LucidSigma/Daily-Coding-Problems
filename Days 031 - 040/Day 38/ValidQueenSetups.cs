using System;
using System.Collections.Generic;

namespace DailyCodingProblem
{
	internal class Day38
	{
		private static int Main(string[] args)
		{
			Console.WriteLine($"Total solutions for N = 2: {GetValidQueenSetups(2)}");
			Console.WriteLine($"Total solutions for N = 4: {GetValidQueenSetups(4)}");
			Console.WriteLine($"Total solutions for N = 8: {GetValidQueenSetups(8)}");

			Console.ReadLine();

			return 0;
		}

		private static int GetValidQueenSetups(int n)
		{
			List<int> board = new List<int>();

			return GetValidQueenSetupsHelper(board, n);
		}

		private static int GetValidQueenSetupsHelper(List<int> board, int n)
		{
			if (board.Count == n)
			{
				return 1;
			}

			int count = 0;

			for (int i= 0; i < n; i++)
			{
				board.Add(i);
				
				if (IsValidQueenSetup(board))
				{
					count += GetValidQueenSetupsHelper(board, n);
				}

				board.RemoveAt(board.Count - 1);
			}

			return count;
		}

		private static bool IsValidQueenSetup(List<int> board)
		{
			int lastRow = board.Count - 1;
			int lastColumn = board[lastRow];

			for (int i = 0; i < lastRow; i++)
			{
				int difference = Math.Abs(lastColumn - board[i]);

				if (difference == 0 || difference == lastRow - i)
				{
					return false;
				}
			}

			return true;
		}
	}
}