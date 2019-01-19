using System;

namespace DailyCodingProblem
{
	internal class Day34
	{
		private static int Main(string[] args)
		{
			Console.WriteLine(GetMinimumPalindrone("racecar"));
			Console.WriteLine(GetMinimumPalindrone("race"));
			Console.WriteLine(GetMinimumPalindrone("google"));

			Console.ReadLine();

			return 0;
		}

		private static string GetMinimumPalindrone(string text)
		{
			if (IsPalindrome(text))
			{
				return text;
			}

			if (text[0] == text[text.Length - 1])
			{
				return text[0] + GetMinimumPalindrone(text.Substring(1, text.Length - 2)) + text[text.Length - 1];
			}

			string firstPalindrome = text[0] + GetMinimumPalindrone(text.Substring(1)) + text[0];
			string secondPalindrome = text[text.Length - 1] + GetMinimumPalindrone(text.Substring(0, text.Length - 1)) + text[text.Length - 1];

			if (firstPalindrome.Length > secondPalindrome.Length)
			{
				return secondPalindrome;
			}
			else if (firstPalindrome.Length < secondPalindrome.Length)
			{
				return firstPalindrome;
			}
			else
			{
				return string.Compare(firstPalindrome, secondPalindrome) <= 0 ? firstPalindrome : secondPalindrome;
			}
		}

		private static bool IsPalindrome(string text)
		{
			char[] chars = text.ToCharArray();
			Array.Reverse(chars);

			return text == new string(chars);
		}
	}
}