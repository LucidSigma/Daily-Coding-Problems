using System;
using System.Collections.Generic;

namespace DailyCodingProblem
{
	internal class Day7
	{
		private static int Main(string[] args)
		{
			Console.WriteLine(GetAllDecodings("111"));
			Console.WriteLine(GetAllDecodings("1112"));
			Console.WriteLine(GetAllDecodings("1220487311121120348981012121"));

			Console.ReadLine();

			return 0;
		}
		
		private static int GetAllDecodings(string code)
		{
			List<int> results = new List<int>(code.Length + 1) { 1, 1 };

			for (int i = 2; i < code.Length + 1; i++)
			{
				results.Add(0);

				if (code[i - 1] > '0')
				{
					results[i] = results[i - 1];
				}

				if (code[i - 2] == '1' || (code[i - 2] == '2' && code[i - 1] < '7'))
				{
					results[i] += results[i - 2];
				}
			}

			return results[results.Count - 1];
		}
	}
}