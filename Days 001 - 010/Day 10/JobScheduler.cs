using System;
using System.Threading;

namespace DailyCodingProblem
{
	internal class JobScheduler
	{
		public static void ScheduleJob(Action function, int callback)
		{
			Thread.Sleep(callback);

			function();
		}
	}

	internal class Day10
	{
		private static int Main(string[] args)
		{
			JobScheduler.ScheduleJob(JobA, 1500);
			JobScheduler.ScheduleJob(JobB, 500);
			JobScheduler.ScheduleJob(JobC, 3250);

			Console.ReadLine();

			return 0;
		}

		private static void JobA()
		{
			Console.WriteLine("Job A completed.");
		}

		private static void JobB()
		{
			Console.WriteLine("Job B completed.");
		}

		private static void JobC()
		{
			Console.WriteLine("Job C completed.");
		}
	}
}