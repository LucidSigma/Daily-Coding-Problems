using System;
using System.Collections.Generic;
using System.Linq;

namespace DailyCodingProblem
{
	internal class Path
	{
		public HashSet<string> Nodes { get; set; } = new HashSet<string>();
		public Dictionary<char, int> LetterCounts { get; set; } = new Dictionary<char, int>();
	}

	internal class Day72
	{
		private static int Main(string[] args)
		{
			List<(int, int)> nodes = new List<(int, int)>
			{
				(0, 1), (0, 2), (2, 3), (3, 4)
			};

			Console.WriteLine(GetMostVisitedNodeCount("ABACA", nodes));
			Console.WriteLine(GetMostVisitedNodeCount("A", new List<(int, int)> { (0, 0) }));

			Console.ReadLine();

			return 0;
		}

		private static int GetMostVisitedNodeCount(string input, List<(int, int)> edges)
		{
			Dictionary<char, int> letterCounts = new Dictionary<char, int>();
			List<string> nodes = new List<string>();

			foreach (char c in input)
			{
				if (!letterCounts.ContainsKey(c))
				{
					letterCounts[c] = 0;
				}

				letterCounts[c]++;
				nodes.Add(c + letterCounts[c].ToString());
			}

			Dictionary<string, HashSet<string>> adjacencies = new Dictionary<string, HashSet<string>>();

			foreach ((int start, int end) in edges)
			{
				if (nodes[start] != nodes[end] || (nodes[start].Length == 0 && nodes[end].Length == 0))
				{
					if (!adjacencies.ContainsKey(nodes[start]))
					{
						adjacencies[nodes[start]] = new HashSet<string>();
					}

					adjacencies[nodes[start]].Add(nodes[end]);
				}
			}

			List<Path> paths = new List<Path>();
			Path graphPath = new Path();

			foreach (var node in adjacencies)
			{
				List<Path> newPaths = GetMostVisitedNodeCountHelper(graphPath, node.Key, adjacencies);
				paths.Concat(newPaths);
			}

			int maxCount = 0;

			foreach (Path path in paths)
			{
				int pathMax = 0;

				foreach (var letterCount in path.LetterCounts)
				{
					pathMax = Math.Max(pathMax, letterCount.Value);
				}

				maxCount = Math.Max(maxCount, pathMax);
			}

			const int InfiniteLoop = int.MaxValue;

			return maxCount > 0 ? maxCount : InfiniteLoop;
		}

		private static List<Path> GetMostVisitedNodeCountHelper(Path path, string node, Dictionary<string, HashSet<string>> adjacencies)
		{
			if (path.Nodes.Contains(node))
			{
				return new List<Path> { path };
			}

			Dictionary<char, int> newLetterCounts = new Dictionary<char, int>(path.LetterCounts);
			HashSet<string> newNodes = new HashSet<string>(path.Nodes) { node };

			if (!newLetterCounts.ContainsKey(node[0]))
			{
				newLetterCounts[node[0]] = 0;
			}

			newLetterCounts[node[0]]++;

			Path newPath = new Path
			{
				Nodes = newNodes,
				LetterCounts = newLetterCounts
			};

			if (!adjacencies.ContainsKey(node))
			{
				return new List<Path> { newPath };
			}

			List<Path> paths = new List<Path>();

			foreach (string child in adjacencies[node])
			{
				List<Path> newPaths = GetMostVisitedNodeCountHelper(newPath, child, adjacencies);
				paths.Concat(newPaths);
			}

			return paths;
		}
	}
}