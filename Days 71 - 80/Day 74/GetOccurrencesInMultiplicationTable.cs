using System;

namespace DailyCodingProblem
{
	internal class Day74
	{
		private static int Main(string[] args)
		{
			Console.WriteLine(GetOccurrencesInMultiplicationTable(6, 12));

			Console.ReadLine();

			return 0;
		}

		private static int GetOccurrencesInMultiplicationTable(int n, int x)
		{
			int occurrenceCount = 0;

			for (int i = 1; i <= n; i++)
			{
				if (x % i == 0 && x / i <= n)
				{
					occurrenceCount++;
				}
			}

			return occurrenceCount;
		}
	}
}