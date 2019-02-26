using System;
using System.Collections.Generic;
using System.Linq;

namespace DailyCodingProblem
{
	internal class Day57
	{
		private static int Main(string[] args)
		{
			string sentence = "The quick brown fox jumps over the lazy dog.";
			PrintList(BreakStringIntoTexts(sentence, 10));

			Console.WriteLine();

			sentence = "12345678910";
			PrintList(BreakStringIntoTexts(sentence, 10));

			Console.ReadLine();

			return 0;
		}

		private static List<string> BreakStringIntoTexts(string text, int k)
		{
			List<string> texts = new List<string>();
			List<string> words = text.Split(' ').ToList();
			string currentText = "";

			foreach (string word in words)
			{
				if ((currentText + word).Length - 1 < k)
				{
					currentText += word;
				}
				else if (word.Length > k)
				{
					return new List<string>();
				}
				else
				{
					currentText.Remove(currentText.Length - 1);
					texts.Add(currentText);
					currentText = word;
				}

				currentText += ' ';
			}

			currentText.Remove(currentText.Length - 1);
			texts.Add(currentText);

			return texts;
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
				Console.WriteLine($"{value} ");
			}
		}
	}
}