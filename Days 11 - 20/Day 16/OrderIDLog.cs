using System;
using System.Collections;
using System.Collections.Generic;
using System.Linq;

namespace DailyCodingProblem
{
	internal class OrderList : IEnumerable
	{
		private LinkedList<int> idHistory = new LinkedList<int>();
		private int size;

		public int Size
		{
			get => size;

			set
			{
				size = value;

				if (size < CurrentSize)
				{
					int oldSize = CurrentSize;

					for (int i = 0; i < oldSize - size; i++)
					{
						idHistory.RemoveFirst();
					}
				}
			}
		}

		public int CurrentSize => idHistory.Count;

		public OrderList(int size)
		{
			this.size = size;
		}

		public void Record(params int[] ids)
		{
			foreach (int id in ids)
			{
				idHistory.AddLast(id);

				if (CurrentSize > Size)
				{
					idHistory.RemoveFirst();
				}
			}
		}

		public int GetLast(int i = 0)
		{
			if (i < CurrentSize)
			{
				return idHistory.ElementAt(CurrentSize - i - 1);
			}
			else
			{
				throw new IndexOutOfRangeException("Index out of range of ID history.");
			}
		}

		public IEnumerator GetEnumerator()
		{
			foreach (int id in idHistory)
			{
				yield return id;
			}
		}
	}

	internal class Day16
	{
		private static int Main(string[] args)
		{
			OrderList orderList = new OrderList(10);
			orderList.Record(1, 45, 6, 3, 8, 3);

			for (int i = 0; i < orderList.CurrentSize; i++)
			{
				Console.WriteLine(orderList.GetLast(i));
			}
			
			Console.ReadLine();

			return 0;
		}
	}
}