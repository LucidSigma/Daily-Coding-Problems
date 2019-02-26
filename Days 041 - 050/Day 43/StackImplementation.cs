using System;
using System.Collections.Generic;

namespace DailyCodingProblem
{
	internal class Stack
	{
		private List<int> data = new List<int>();
		private List<int> maximums = new List<int>();

		public int Max
		{
			get
			{
				if (data.Count == 0)
				{
					throw new InvalidOperationException("Stack is empty.");
				}

				return data[maximums[maximums.Count - 1]];
			}
		}

		public void Push(int value)
		{
			data.Add(value);

			if (maximums.Count == 0 || value > data[maximums[maximums.Count - 1]])
			{
				maximums.Add(data.Count - 1);
			}
		}

		public int Pop()
		{
			if (data.Count == 0)
			{
				throw new InvalidOperationException("No data to remove from stack.");
			}

			if (data.Count - 1 == maximums[maximums.Count - 1])
			{
				maximums.RemoveAt(maximums.Count - 1);
			}

			int poppedValue = data[data.Count - 1];
			data.RemoveAt(data.Count - 1);

			return poppedValue;
		}
	}

	internal class Day43
	{
		private static int Main(string[] args)
		{
			Stack stack = new Stack();

			stack.Push(3);
			stack.Push(1);
			stack.Push(4);
			stack.Push(5);
			stack.Push(2);
			Console.WriteLine(stack.Max);

			stack.Pop();
			stack.Pop();
			Console.WriteLine(stack.Max);

			stack.Pop();
			Console.WriteLine(stack.Max);

			Console.ReadLine();

			return 0;
		}
	}
}