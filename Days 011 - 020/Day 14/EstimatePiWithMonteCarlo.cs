using System;

namespace DailyCodingProblem
{
	internal class Day14
	{
		private static Random rng = new Random();

		private static int Main(string[] args)
		{
			Console.WriteLine(EstimatePiWithMonteCarlo(10_000_000));

			Console.ReadLine();

			return 0;
		}

		private static decimal EstimatePiWithMonteCarlo(long iterations)
		{
			const decimal Radius = 0.5m;
			const decimal RadiusPiRatio = 1.0m / (Radius * Radius);

			long innerCount = 0;

			for (long i = 0; i < iterations; i++)
			{
				decimal x = ((decimal)rng.NextDouble() * 2.0m * Radius) - Radius;
				decimal y = ((decimal)rng.NextDouble() * 2.0m * Radius) - Radius;

				if (x * x + y * y <= Radius * Radius)
				{
					innerCount++;
				}
			}

			return RadiusPiRatio * innerCount / iterations;
		}
	}
}