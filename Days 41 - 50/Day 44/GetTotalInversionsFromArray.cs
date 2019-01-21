using System;
using System.Collections.Generic;

namespace DailyCodingProblem
{
	internal class Day44
	{
		private static int Main(string[] args)
		{
			List<int> numbers = new List<int>() { 2, 4, 1, 3, 5 };
			Console.WriteLine(GetTotalInversions(numbers));

			numbers = new List<int>() { 5, 4, 3, 2, 1 };
			Console.WriteLine(GetTotalInversions(numbers));

			Console.ReadLine();

			return 0;
		}

		private static int GetTotalInversions(List<int> numbers) => MergeSort(numbers).Item2;

		private static (List<int>, int) MergeSort(List<int> numbers)
		{
			if (numbers.Count <= 1)
			{
				return (numbers, 0);
			}

			int midPoint = numbers.Count / 2;

			return Merge(MergeSort(numbers.GetRange(0, midPoint)), MergeSort(numbers.GetRange(midPoint, numbers.Count - midPoint)));
		}

		private static (List<int>, int) Merge((List<int>, int) firstHalf, (List<int>, int) secondHalf)
		{
			int i = 0;
			int j = 0;
			List<int> mergedList = new List<int>(firstHalf.Item1.Count + secondHalf.Item1.Count);

			(List<int> firstList, int firstInversions) = firstHalf;
			(List<int> secondList, int secondInversions) = secondHalf;

			int totalInversions = firstInversions + secondInversions;

			while (i < firstList.Count && j < secondList.Count)
			{
				if (firstList[i] < secondList[j])
				{
					mergedList.Add(firstList[i]);
					i++;
				}
				else
				{
					mergedList.Add(secondList[j]);
					totalInversions += firstList.Count - i;
					j++;
				}
			}

			while (i < firstList.Count)
			{
				mergedList.Add(firstList[i]);
				i++;
			}

			while (j < secondList.Count)
			{
				mergedList.Add(secondList[j]);
				j++;
			}

			return (mergedList, totalInversions);
		}
	}
}