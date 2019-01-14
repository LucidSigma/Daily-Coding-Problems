using System;
using System.Collections.Generic;

namespace DailyCodingProblems
{
	internal class Day2
	{
		private static int Main(string[] args)
		{
			int[] numbers = new int[] { 1, 2, 3, 4, 5 };
			Console.WriteLine(ArrayToString(GetProductsOfOtherElements(numbers)));

			numbers = new int[] { 3, 2, 1 };
			Console.WriteLine(ArrayToString(GetProductsOfOtherElements(numbers)));

			Console.ReadLine();

			return 0;
		}

		private static int[] GetProductsOfOtherElements(int[] numbers)
		{
			int productCounter = 1;
			List<int> lessProducts = new List<int>(numbers.Length);

			for (int i = 0; i < numbers.Length; i++)
			{
				lessProducts.Add(productCounter);
				productCounter *= numbers[i];
			}

			productCounter = 1;
			List<int> greaterProducts = new List<int>(numbers.Length);

			for (int i = numbers.Length - 1; i >= 0; i--)
			{
				greaterProducts.Add(productCounter);
				productCounter *= numbers[i];
			}

			List<int> finalProducts = new List<int>(numbers.Length);

			for (int i = 0; i < numbers.Length; i++)
			{
				finalProducts.Add(lessProducts[i] * greaterProducts[greaterProducts.Count - i - 1]);
			}

			return finalProducts.ToArray();
		}

		private static string ArrayToString<T>(T[] array)
		{
			string arrayString = "";

			foreach (T value in array)
			{
				arrayString += value + " ";
			}

			return arrayString;
		}
	}
}