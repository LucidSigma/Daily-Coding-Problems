using System;
using System.Collections.Generic;

namespace DailyCodingProblem
{
	internal struct Bishop
	{
		public int X { get; }
		public int Y { get; }

		public Bishop(int x, int y)
		{
			this.X = x;
			this.Y = y;
		}
	}

	internal class Day68
	{
		private static int Main(string[] args)
		{
			List<Bishop> bishops = new List<Bishop>
			{
				new Bishop(0, 0),
				new Bishop(1, 2),
				new Bishop(2, 2),
				new Bishop(4, 0)
			};

			Console.WriteLine(GetBishopAttackPairCount(bishops, 5));

			Console.ReadLine();

			return 0;
		}

		private static int GetBishopAttackPairCount(List<Bishop> bishopLocations, int m)
		{
			if (m <= 0)
			{
				return 0;
			}

			int pairCount = 0;
			var bishopStack = new List<Bishop>(bishopLocations);

			while (bishopStack.Count > 1)
			{
				Bishop currentBishop = bishopStack[bishopStack.Count - 1];

				if (currentBishop.X < m && currentBishop.X >= 0 &&
					currentBishop.Y < m && currentBishop.Y >= 0)
				{
					for (int i = bishopStack.Count - 2; i >= 0; i--)
					{
						Bishop otherBishop = bishopStack[i];

						if (otherBishop.X >= m || otherBishop.X < 0 ||
							otherBishop.Y >= m || otherBishop.Y < 0)
						{
							continue;
						}

						int xDifference = Math.Abs(currentBishop.X - otherBishop.X);
						int yDifference = Math.Abs(currentBishop.Y - otherBishop.Y);

						if (xDifference == yDifference)
						{
							pairCount++;
						}
					}
				}

				bishopStack.RemoveAt(bishopStack.Count - 1);
			}

			return pairCount;
		}
	}
}