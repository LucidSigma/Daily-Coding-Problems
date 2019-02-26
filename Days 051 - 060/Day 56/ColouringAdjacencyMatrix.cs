using System;
using System.Linq;

namespace DailyCodingProblem
{
	internal class Day56
	{
		private static int Main(string[] args)
		{
			int[][] adjacencyMatrix = new int[][]
			{
				new int[] { 0, 0, 1, 1, 0 },
				new int[] { 0, 0, 1, 1, 1 },
				new int[] { 1, 1, 0, 1, 0 },
				new int[] { 1, 1, 1, 0, 1 },
				new int[] { 0, 1, 0, 1, 0 }
			};

			Console.WriteLine(CanUniquelyColourAdjacentVertices(adjacencyMatrix, 5));

			Console.ReadLine();

			return 0;
		}

		private static bool CanUniquelyColourAdjacentVertices(int[][] adjacencyMatrix, int colours)
		{
			int maxAdjacencies = 0;

			for (int i = 0; i < adjacencyMatrix.Length; i++)
			{
				int sum = adjacencyMatrix[i].Sum();
				maxAdjacencies = Math.Max(maxAdjacencies, sum);
			}

			return colours > maxAdjacencies;
		}
	}
}