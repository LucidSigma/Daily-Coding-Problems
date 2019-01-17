using System;
using System.Collections.Generic;
using System.Linq;

namespace DailyCodingProblem
{
	internal class Day17
	{
		private static int Main(string[] args)
		{
			Console.WriteLine(LengthOfLongestPath(""));
			Console.WriteLine(LengthOfLongestPath("dir\n\tfile.ext"));
			Console.WriteLine(LengthOfLongestPath("dir\n\tsubdir1\n\tsubdir2\n\t\tfile.ext"));
			Console.WriteLine(LengthOfLongestPath("dir\n\tsubdir1\n\t\tfile1.ext\n\t\tsubsubdir1\n\tsubdir2\n\t\tsubsubdir2\n\t\t\tfile2.ext"));

			Console.ReadLine();

			return 0;
		}

		private static int LengthOfLongestPath(string filePath)
		{
			List<string> directories = filePath.Split('\n').ToList();
			List<int> lengths = new List<int>(directories.Count + 1);

			for (int i = 0; i < directories.Count + 1; i++)
			{
				lengths.Add(0);
			}

			int maxLength = 0;

			foreach (string directory in directories)
			{
				int currentLevel = directory.LastIndexOf('\t') + 1;
				int currentLength = lengths[currentLevel] + directory.Length - currentLevel + 1;
				lengths[currentLevel + 1] = currentLength;

				if (directory.Contains('.'))
				{
					maxLength = Math.Max(maxLength, currentLength - 1);
				}
			}

			return maxLength;
		}
	}
}