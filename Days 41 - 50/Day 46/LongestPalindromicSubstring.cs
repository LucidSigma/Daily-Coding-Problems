using System;

namespace DailyCodingProblem
{
	internal class Day46
	{
		private static int Main(string[] args)
		{
			Console.WriteLine(GetLongestPalindromicSubstring("aabcdcb"));
			Console.WriteLine(GetLongestPalindromicSubstring("bananas"));

			Console.ReadLine();

			return 0;
		}

		private static string GetLongestPalindromicSubstring(string text)
		{
			if (text.Length == 0 || IsPalindrome(text))
			{
				return text;
			}

			string withoutFirst = GetLongestPalindromicSubstring(text.Substring(1));
			string withoutLast = GetLongestPalindromicSubstring(text.Substring(0, text.Length - 1));

			return withoutFirst.Length >= withoutLast.Length ? withoutFirst : withoutLast;
		}

		private static bool IsPalindrome(string text)
		{
			char[] chars = text.ToCharArray();
			Array.Reverse(chars);

			return text == new string(chars);
		}
	}
}