using System;
using System.Collections.Generic;

namespace DailyCodingProblem
{
	internal class Day22
	{
		private static int Main(string[] args)
		{
			SortedSet<string> dictionary = new SortedSet<string> { "quick", "brown", "the", "fox" };
			string sentence = "thequickbrownfox";
			PrintList(GetOriginalSentence(sentence, dictionary));

			dictionary = new SortedSet<string> { "bed", "bath", "bedbath", "and", "beyond" };
			sentence = "bedbathandbeyond";
			PrintList(GetOriginalSentence(sentence, dictionary));

			dictionary = new SortedSet<string> { "this", "will", "return", "an", "empty", "list" };
			sentence = "nodictionarywordsinhere";
			PrintList(GetOriginalSentence(sentence, dictionary));

			Console.ReadLine();

			return 0;
		}

		private static List<string> GetOriginalSentence(string sentence, SortedSet<string> dictionary)
		{
			List<string> words = new List<string>();
			string searchString = sentence;

			while (!string.IsNullOrEmpty(searchString))
			{
				bool wordFound = false;

				foreach (string word in dictionary)
				{
					if (searchString.StartsWith(word))
					{
						words.Add(word);

						searchString = searchString.Substring(word.Length);
						wordFound = true;
					}
				}

				if (!wordFound)
				{
					return new List<string>();
				}
			}

			return words;
		}

		private static void PrintList<T>(List<T> list)
		{
			if (list.Count == 0)
			{
				Console.WriteLine("List is empty...");

				return;
			}

			foreach (T value in list)
			{
				Console.Write($"{value} ");
			}

			Console.WriteLine();
		}
	}
}