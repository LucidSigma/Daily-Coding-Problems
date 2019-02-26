using System;
using System.Collections.Generic;

namespace DailyCodingProblem
{
	internal struct Point
	{
		public int x;
		public int y;

		public Point(int x, int y)
		{
			this.x = x;
			this.y = y;
		}

		public override bool Equals(object obj)
		{
			if (!(obj is Point))
			{
				return false;
			}

			var point = (Point)obj;
			return x == point.x && y == point.y;
		}

		public override int GetHashCode() => base.GetHashCode();

		public static bool operator ==(Point lhs, Point rhs) => lhs.Equals(rhs);
		public static bool operator !=(Point lhs, Point rhs) => !lhs.Equals(rhs);
	}

	internal struct Node
	{
		public Point point;
		public int distance;

		public Node(Point point, int distance)
		{
			this.point = point;
			this.distance = distance;
		}
	}

	internal class Day23
	{
		private static int Main(string[] args)
		{
			bool[,] matrix = new bool[,]
			{
				{ false, false, false, false },
				{  true,  true, false,  true },
				{ false, false, false, false },
				{ false, false, false, false }
			};

			Point start = new Point(3, 0);
			Point end = new Point(0, 0);

			Console.WriteLine(GetStepCount(matrix, start, end));

			Console.ReadLine();

			return 0;
		}

		private static int GetStepCount(bool[,] matrix, Point start, Point end)
		{
			const int InvalidPath = -1;

			if (matrix[start.x, start.y] || matrix[end.x, end.y])
			{
				return InvalidPath;
			}

			bool[,] visitedPoints = new bool[matrix.GetLength(0), matrix.GetLength(1)];
			visitedPoints[start.x, start.y] = true;

			Queue<Node> nodes = new Queue<Node>();
			nodes.Enqueue(new Node(start, 0));

			while (nodes.Count > 0)
			{
				Node currentNode = nodes.Peek();
				Point currentPoint = currentNode.point;

				if (currentPoint == end)
				{
					return currentNode.distance;
				}

				nodes.Dequeue();

				const int SurroundingNodes = 4;
				int[] rowRelations = new int[SurroundingNodes] { -1, 0, 0, 1 };
				int[] columnRelations = new int[SurroundingNodes] { 0, -1, 1, 0 };

				for (int i = 0; i < SurroundingNodes; i++)
				{
					int currentRow = currentPoint.x + rowRelations[i];
					int currentColumn = currentPoint.y + columnRelations[i];

					if (IsInMatrix(currentRow, currentColumn, matrix.GetLength(0), matrix.GetLength(1)) && !matrix[currentRow, currentColumn] && !visitedPoints[currentRow, currentColumn])
					{
						visitedPoints[currentRow, currentColumn] = true;

						Point targetPoint = new Point(currentRow, currentColumn);
						Node targetNode = new Node(targetPoint, currentNode.distance + 1);

						nodes.Enqueue(targetNode);
					}
				}
			}

			return InvalidPath;
		}

		private static bool IsInMatrix(int row, int column, int rowCount, int columnCount) => row < rowCount && row >= 0 && column < columnCount && column >= 0;
	}
}