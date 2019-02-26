using System;

namespace DailyCodingProblem
{
	internal class Day21
	{
		private static int Main(string[] args)
		{
			(int, int)[] times = { (30, 75), (0, 50), (60, 150) };

			Console.WriteLine($"Classrooms needed: {FindClassroomCount(times)}");

			Console.ReadLine();

			return 0;
		}

		private static int FindClassroomCount((int, int)[] intervals)
		{
			int[] starts = new int[intervals.Length];
			int[] ends = new int[intervals.Length];

			for (int i = 0; i < intervals.Length; i++)
			{
				starts[i] = intervals[i].Item1;
				ends[i] = intervals[i].Item2;
			}

			Array.Sort(starts);
			Array.Sort(ends);

			int currentClassroomsNeeded = 1;
			int totalClassroomsNeeded = 1;
			int startCount = 1;
			int endCount = 0;

			while (startCount < intervals.Length && endCount < intervals.Length)
			{
				if (starts[startCount] <= ends[endCount])
				{
					currentClassroomsNeeded++;
					startCount++;

					if (currentClassroomsNeeded > totalClassroomsNeeded)
					{
						totalClassroomsNeeded = currentClassroomsNeeded;
					}
				}
				else
				{
					currentClassroomsNeeded--;
					endCount++;
				}
			}

			return totalClassroomsNeeded;
		}
	}
}