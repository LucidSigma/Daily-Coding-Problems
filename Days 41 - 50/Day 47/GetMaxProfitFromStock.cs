using System;

namespace DailyCodingProblem
{
	internal class Day47
	{
		private static int Main(string[] args)
		{
			int[] stocks = new int[] { 9, 11, 8, 5, 7, 10 };
			Console.WriteLine(GetMaxProfitFromStock(stocks));

			Console.ReadLine();

			return 0;
		}

		private static int GetMaxProfitFromStock(int[] stocks)
		{
			if (stocks.Length <= 1)
			{
				throw new ArgumentException("Stocks array is too small.");
			}

			int minStock = stocks[0];
			int maxProfit = int.MinValue;

			for (int i = 1; i < stocks.Length; i++)
			{
				maxProfit = Math.Max(stocks[i] - minStock, maxProfit);
				minStock = Math.Min(stocks[i], minStock);
			}

			return maxProfit;
		}
	}
}