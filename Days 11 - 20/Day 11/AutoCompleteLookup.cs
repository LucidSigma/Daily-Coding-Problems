using System;
using System.Collections.Generic;
using System.Linq;

namespace DailyCodingProblem
{
	internal class Day11
	{
		private static SortedSet<string> dictionary = new SortedSet<string>();

		private static int Main(string[] args)
		{
			AddWordsToDictionary("dog", "deer", "deal");
			PrintList(GetPossibleWords("de"));

			Console.ReadLine();

			return 0;
		}

		private static List<string> GetPossibleWords(string query)
		{
			return (from word in dictionary
					where word.StartsWith(query)
					select word).ToList();
		}

		private static void AddWordsToDictionary(params string[] words)
		{
			foreach (string word in words)
			{
				dictionary.Add(word);
			}
		}

		private static void PrintList<T>(List<T> list, string delimiter = " ")
		{
			foreach (T value in list)
			{
				Console.Write($"{value} ");
			}

			Console.WriteLine();
		}
	}
}