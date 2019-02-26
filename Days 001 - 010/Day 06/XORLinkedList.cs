using System;
using System.Collections;
using System.Runtime.InteropServices;

namespace DailyCodingProblem
{
	internal unsafe class XorList : IEnumerable
	{
		private unsafe struct Node
		{
			public int data;
			public Node* xorAddress;

			public Node(int data, Node* previous, Node* next)
			{
				this.data = data;
				this.xorAddress = XorList.XorAddresses(previous, next);
			}
		}

		private static Node* XorAddresses(Node* previous, Node* next)
		{
			return (Node*)((int)previous ^ (int)next);
		}

		private Node* head;
		private int size;

		public XorList()
		{
			head = null;
			size = 0;
		}

		~XorList()
		{
			if (head != null)
			{
				DestroyNode(null, head);
			}
		}

		public void Add(int data)
		{
			if (head == null)
			{
				head = AllocateNode(data, null, null);
			}
			else
			{
				Node* previous = null;
				Node* current = head;
				Node* next = XorAddresses(previous, current->xorAddress);

				while (next != null)
				{
					previous = current;
					current = next;
					next = XorAddresses(previous, current->xorAddress);
				}

				Node* node = AllocateNode(data, current, null);
				current->xorAddress = XorAddresses(previous, node);
			}

			size++;
		}

		public int Get(int index)
		{
			Node* previous = null;
			Node* current = head;
			int i = index;

			while ((i > 0) && (current != null))
			{
				Node* next = XorAddresses(previous, current->xorAddress);
				previous = current;
				current = next;

				i--;
			}

			if (i != 0)
			{
				throw new IndexOutOfRangeException($"Index {index} out of range of XOR list.");
			}

			return current->data;
		}

		public int this[int index]
		{
			get { return Get(index); }
		}

		public IEnumerator GetEnumerator()
		{
			for (int i = 0; i < size; i++)
			{
				yield return this[i];
			}
		}

		private Node* AllocateNode(int value, Node* left, Node* right)
		{
			Node* node = (Node*)Marshal.AllocHGlobal(sizeof(Node));

			node->data = value;
			node->xorAddress = XorAddresses(left, right);

			return node;
		}

		private void DestroyNode(Node* previous, Node* current)
		{
			if (current == null)
			{
				return;
			}

			Node* next = XorAddresses(previous, current->xorAddress);

			if (next != null)
			{
				DestroyNode(current, next);
				Marshal.FreeHGlobal((IntPtr)next);
			}
		}
	}

	internal class Day6
	{
		private static int Main(string[] args)
		{
			XorList xorList = new XorList();

			xorList.Add(10);
			xorList.Add(25);
			xorList.Add(42);

			foreach (int number in xorList)
			{
				Console.WriteLine(number);
			}

			try
			{
				Console.WriteLine(xorList[4]);
			}
			catch (IndexOutOfRangeException e)
			{
				Console.WriteLine(e.Message);
			}

			Console.ReadLine();

			return 0;
		}
	}
}