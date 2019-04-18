#include <iostream>
#include <iterator>
#include <vector>

class Stack
{
private:
	static constexpr unsigned int StackCount = 3;

	std::vector<std::vector<int>> list{ StackCount };

public:
	Stack() = default;

	void Pop(const unsigned int stackNumber) noexcept
	{
		if (stackNumber >= list.size())
		{
			return;
		}

		list[stackNumber].pop_back();
	}

	void Push(const int item, unsigned int stackNumber) noexcept
	{
		if (stackNumber < list.size())
		{
			list[stackNumber].push_back(item);
		}
	}

	int Top(const unsigned int stackNumber) const noexcept
	{
		if (stackNumber < list.size())
		{
			return list[stackNumber].back();
		}
	}

	void PrintStacks() const noexcept
	{
		for (unsigned int i = 0; i < list.size(); i++)
		{
			std::cout << "Stack " << (i + 1) << ": ";
			PrintSingleStack(i);
			std::cout << "\n";
		}
	}

private:
	void PrintSingleStack(const unsigned int index) const noexcept
	{
		for (auto it = std::crbegin(list[index]); it != std::crend(list[index]); it++)
		{
			std::cout << *it << " ";
		}
	}
};

int main(int argc, char* argv[])
{
	Stack stack;

	stack.Push(0, 0);
	stack.Push(7, 0);
	stack.Push(9, 0);
	stack.Push(4, 0);

	stack.Push(1, 1);
	stack.Push(6, 1);
	stack.Push(5, 1);

	stack.Push(2, 2);
	stack.Push(0, 2);
	stack.Push(3, 2);
	stack.Push(7, 2);
	stack.Push(4, 2);

	stack.Pop(0);
	stack.Pop(2);
	stack.Pop(2);

	stack.PrintStacks();

	std::cin.get();

	return 0;
}