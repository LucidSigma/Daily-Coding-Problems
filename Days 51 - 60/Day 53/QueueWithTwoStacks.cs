using System;
using System.Collections.Generic;

namespace DailyCodingProblem
{
	internal class Queue
	{
		private Stack<int> stackA = new Stack<int>();
		private Stack<int> stackB = new Stack<int>();

		public void Enqueue(int item)
		{
			stackA.Push(item);
		}

		public void Dequeue()
		{
			if (stackA.Count == 0)
			{
				throw new InvalidOperationException("Queue is empty.");
			}

			SwapStacks(stackA, stackB);
			stackB.Pop();
			SwapStacks(stackB, stackA);
		}

		public int Peek()
		{
			if (stackA.Count == 0)
			{
				throw new InvalidOperationException("Queue is empty.");
			}

			SwapStacks(stackA, stackB);

			int item = stackB.Peek();

			SwapStacks(stackB, stackA);

			return item;
		}

		private void SwapStacks(Stack<int> a, Stack<int> b)
		{
			while (a.Count > 0)
			{
				b.Push(a.Peek());
				a.Pop();
			}
		}
	}

	internal class Day53
	{
		private static int Main(string[] args)
		{
			Queue queue = new Queue();
			queue.Enqueue(5);
			queue.Enqueue(2);
			queue.Enqueue(7);
			Console.WriteLine(queue.Peek());

			queue.Dequeue();
			Console.WriteLine(queue.Peek());

			Console.ReadLine();

			return 0;
		}
	}
}