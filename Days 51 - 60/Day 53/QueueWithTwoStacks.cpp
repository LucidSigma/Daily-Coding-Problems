#include <iostream>
#include <stack>
#include <stdexcept>

class Queue
{
private:
	std::stack<int> stackA;
	std::stack<int> stackB;

public:
	void Enqueue(int value)
	{
		stackA.push(value);
	}

	void Dequeue()
	{
		if (stackA.empty())
		{
			throw std::out_of_range("Queue is empty.");
		}

		SwapStacks(stackA, stackB);
		stackB.pop();

		SwapStacks(stackB, stackA);
	}

	int Peek()
	{
		if (stackA.empty())
		{
			throw std::out_of_range("Queue is empty.");
		}

		SwapStacks(stackA, stackB);

		int value = stackB.top();

		SwapStacks(stackB, stackA);

		return value;
	}

private:
	void SwapStacks(std::stack<int>& a, std::stack<int>& b)
	{
		while (!a.empty())
		{
			b.push(a.top());
			a.pop();
		}
	}
};

int main(int argc, const char* argv[])
{
	Queue queue;

	queue.Enqueue(5);
	queue.Enqueue(2);
	queue.Enqueue(7);
	std::cout << queue.Peek() << "\n";

	queue.Dequeue();
	std::cout << queue.Peek() << "\n";

	std::cin.get();

	return 0;
}
