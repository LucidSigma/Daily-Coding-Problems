using System;
using System.Collections.Generic;
using System.IO;
using System.Text;
using System.Threading;

namespace DailyCodingProblem
{
	internal enum CellStates
	{
		Alive = '*',
		Dead = '.'
	}

	internal struct Cell
	{
		public static int minX = int.MaxValue;
		public static int maxX = int.MinValue;
		public static int minY = int.MaxValue;
		public static int maxY = int.MinValue;

		public int x;
		public int y;

		public Cell(int x, int y)
		{
			this.x = x;
			this.y = y;
		}

		public static bool operator ==(Cell lhs, Cell rhs) => lhs.x == rhs.x && lhs.y == rhs.y;
		public static bool operator !=(Cell lhs, Cell rhs) => !(lhs == rhs);

		public static bool operator <(Cell lhs, Cell rhs) => lhs.x != rhs.x ? lhs.x < rhs.x : lhs.y < rhs.y;
		public static bool operator >(Cell lhs, Cell rhs) => lhs.x != rhs.x ? lhs.x > rhs.x : lhs.y > rhs.y;

		public override bool Equals(object obj)
		{
			if (!(obj is Cell))
			{
				return false;
			}

			Cell cell = (Cell)obj;
			return x == cell.x && y == cell.y;
		}

		public override int GetHashCode() => base.GetHashCode();
	}

	internal class GameOfLife
	{
		private List<Cell> cells;
		private List<StringBuilder> board = new List<StringBuilder>();

		public GameOfLife(List<Cell> cells)
		{
			this.cells = cells;
		}

		public void Play(int iterations = 100, int millisecondDelta = 500)
		{
			UpdateCellMinAndMax();
			CellsToBoard();

			PrintBoard();
			Thread.Sleep(millisecondDelta);

			for (int i = 0; i < iterations; i++)
			{
				board = IterateCells();
				PrintBoard(i + 1);

				Thread.Sleep(millisecondDelta);
			}
		}

		private List<StringBuilder> IterateCells()
		{
			UpdateCellMinAndMax();

			List<Cell> newCells = new List<Cell>();
			List<Cell> deadCells = new List<Cell>();

			if (cells.Count > 0)
			{
				CellsToBoard();

				for (int i = 0; i < board.Count; i++)
				{
					for (int j = 0; j < board[i].Length; j++)
					{
						if (IsAliveCell(i, j))
						{
							const int PopulationMin = 2;
							const int PopulationMax = 3;
							int neighbourCount = GetNeighbourCount(i, j);

							if (neighbourCount < PopulationMin || neighbourCount > PopulationMax)
							{
								deadCells.Add(new Cell(i, j));
							}
						}
					}
				}

				for (int i = 0; i < board.Count; i++)
				{
					for (int j = 0; j < board[i].Length; j++)
					{
						if (!IsAliveCell(i, j))
						{
							const int RebirthCount = 3;
							int neighbourCount = GetNeighbourCount(i, j);

							if (neighbourCount == RebirthCount)
							{
								newCells.Add(new Cell(i, j));
							}
						}
					}
				}

				foreach (Cell cell in newCells)
				{
					board[cell.x][cell.y] = (char)CellStates.Alive;
				}

				foreach (Cell cell in deadCells)
				{
					board[cell.x][cell.y] = (char)CellStates.Dead;
				}

				cells = CreateCellsFromBoard();
			}
			else
			{
				board.Add(new StringBuilder((char)CellStates.Dead, 1));
			}

			return board;
		}

		private void CellsToBoard()
		{
			board = new List<StringBuilder>();

			for (int i = 0; i < Cell.maxX - Cell.minX + 1; i++)
			{
				string row = new string((char)CellStates.Dead, Cell.maxY - Cell.minY + 1);
				board.Add(new StringBuilder(row));
			}

			foreach (Cell cell in cells)
			{
				board[cell.x - Cell.minX][cell.y - Cell.minY] = (char)CellStates.Alive;
			}
		}

		private List<Cell> CreateCellsFromBoard()
		{
			List<Cell> newCells = new List<Cell>();

			for (int i = 0; i < board.Count; i++)
			{
				for (int j = 0; j < board[i].Length; j++)
				{
					if (IsAliveCell(i, j))
					{
						newCells.Add(new Cell(i, j));
					}
				}
			}

			return newCells;
		}

		private void UpdateCellMinAndMax()
		{
			Cell.minX = int.MaxValue;
			Cell.maxX = int.MinValue;
			Cell.minY = int.MaxValue;
			Cell.maxY = int.MinValue;

			foreach (Cell cell in cells)
			{
				Cell.minX = Math.Min(cell.x, Cell.minX);
				Cell.maxX = Math.Max(cell.x, Cell.maxX);
				Cell.minY = Math.Min(cell.y, Cell.minY);
				Cell.maxY = Math.Max(cell.y, Cell.maxY);
			}

			Cell.minX--;
			Cell.maxX++;
			Cell.minY--;
			Cell.maxY++;
		}

		private int GetNeighbourCount( int x, int y)
		{
			int count = 0;

			if (x > 0)
			{
				if (y > 0)
				{
					if (IsAliveCell(x - 1, y - 1))
					{
						count++;
					}
				}

				if (IsAliveCell(x - 1, y))
				{
					count++;
				}

				if (y < board[x].Length - 1)
				{
					if (IsAliveCell(x - 1, y + 1))
					{
						count++;
					}
				}
			}

			if (x < board.Count - 1)
			{
				if (y > 0)
				{
					if (IsAliveCell(x + 1, y - 1))
					{
						count++;
					}
				}

				if (IsAliveCell(x + 1, y))
				{
					count++;
				}

				if (y < board[x].Length - 1)
				{
					if (IsAliveCell(x + 1, y + 1))
					{
						count++;
					}
				}
			}

			if (y > 0)
			{
				if (IsAliveCell(x, y - 1))
				{
					count++;
				}
			}

			if (y < board[x].Length - 1)
			{
				if (IsAliveCell(x, y + 1))
				{
					count++;
				}
			}

			return count;
		}

		private void PrintBoard(int iteration = 0)
		{
			Console.Clear();
			Console.WriteLine($"Iteration {iteration}");

			foreach (StringBuilder row in board)
			{
				Console.WriteLine(row);
			}
		}

		private bool IsAliveCell(int x, int y) => board[x][y] == (char)CellStates.Alive;
	}

	internal class Day39
	{
		private static int Main(string[] args)
		{
			List<Cell> cells = GetCellsFromFile("Board.txt");
			GameOfLife gameOfLife = new GameOfLife(cells);

			gameOfLife.Play();

			Console.ReadLine();

			return 0;
		}

		private static List<Cell> GetCellsFromFile(string filename)
		{
			string[] lines = File.ReadAllLines(filename);
			List<Cell> cells = new List<Cell>();

			for (int i = 0; i < lines.Length; i++)
			{
				for (int j = 0; j < lines[i].Length; j++)
				{
					if (lines[i][j] == (char)CellStates.Alive)
					{
						cells.Add(new Cell(i, j));
					}
				}
			}

			return cells;
		}
	}
}