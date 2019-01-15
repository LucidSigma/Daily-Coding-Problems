using System;

namespace DailyCodingProblems
{
	internal class Day5
	{
		private delegate int PairFunction(int a, int b);
		private delegate int ReturnedFunction(PairFunction f);

		private static int Main(string[] args)
		{
			Console.WriteLine(Car(Cons(3, 4)));
			Console.WriteLine(Cdr(Cons(3, 4)));

			Console.ReadLine();

			return 0;
		}

		private static ReturnedFunction Cons(int a, int b)
		{
			int Pair(PairFunction f) => f(a, b);

			return Pair;
		}

		private static int Car(ReturnedFunction pair)
		{
			int First(int a, int b) => a;

			return pair(First);
		}

		private static int Cdr(ReturnedFunction pair)
		{
			int Second(int a, int b) => b;

			return pair(Second);
		}
	}
}