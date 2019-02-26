using System;

namespace DailyCodingProblem
{
	internal class Day32
	{
		private static int Main(string[] args)
		{
			// Currencies: AUD, USD, GBP, EUR, CAD
			double[,] exchangeRates = new double[5, 5]
			{
				{ 1.00, 0.70, 0.55, 0.62, 0.96 },
				{ 1.42, 1.00, 0.79, 0.87, 1.36 },
				{ 1.80, 1.27, 1.00, 1.11, 1.73 },
				{ 1.62, 1.14, 0.90, 1.00, 1.56 },
				{ 1.04, 0.73, 0.58, 0.64, 1.00 }
			};

			Console.WriteLine(HasArbitrage(exchangeRates));

			Console.ReadLine();

			return 0;
		}

		private static bool HasArbitrage(double[,] exchanges)
		{
			double[,] transformedExchanges = new double[exchanges.GetLength(0), exchanges.GetLength(1)];

			for (int i = 0; i < transformedExchanges.GetLength(0); i++)
			{
				for (int j = 0; j < transformedExchanges.GetLength(1); j++)
				{
					transformedExchanges[i, j] = -Math.Log(exchanges[i, j]);
				}
			}

			double[] minDistance = new double[exchanges.GetLength(0)];

			for (int i = 0; i < minDistance.Length; i++)
			{
				minDistance[i] = double.MaxValue;
			}

			minDistance[0] = 0.0;

			for (int i = 0; i < transformedExchanges.GetLength(0) - 1; i++)
			{
				for (int j = 0; j < transformedExchanges.GetLength(0); j++)
				{
					for (int k = 0; k < transformedExchanges.GetLength(1); k++)
					{
						minDistance[k] = Math.Min(minDistance[k], minDistance[j] + transformedExchanges[j, k]);
					}
				}
			}

			for (int i = 0; i < transformedExchanges.GetLength(0); i++)
			{
				for (int j = 0; j < transformedExchanges.GetLength(1); j++)
				{
					if (minDistance[j] > minDistance[i] + transformedExchanges[i, j])
					{
						return true;
					}
				}
			}

			return false;
		}
	}
}