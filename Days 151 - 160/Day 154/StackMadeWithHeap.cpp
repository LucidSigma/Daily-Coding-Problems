#include <iostream>
#include <queue>
#include <stdexcept>

template <typename T>
using HeapOrderPair = std::pair<unsigned int, T>;

template <typename T>
inline bool operator <(const HeapOrderPair<T>& lhs, const HeapOrderPair<T>& rhs) noexcept
{
	return lhs.first < rhs.first;
}

template <typename T>
class Stack
{
private:
	std::priority_queue<HeapOrderPair<T>> items;
	unsigned int counter = 0;

public:
	void Push(const T& item) noexcept
	{
		items.push({ counter, item });
		++counter;
	}

	T Pop()
	{
		if (counter == 0)
		{
			throw std::out_of_range("Stack is empty.");
		}

		const auto[_, top] = items.top();
		items.pop();
		--counter;

		return top;
	}
};

int main(int argc, char* argv[])
{
	Stack<int> stack;

	stack.Push(1);
	stack.Push(2);
	stack.Push(3);

	for (unsigned int i = 0; i < 2; ++i)
	{
		std::cout << stack.Pop() << "\n";
	}

	stack.Push(4);

	for (unsigned int i = 0; i < 2; ++i)
	{
		std::cout << stack.Pop() << "\n";
	}

	std::cin.get();

	return 0;
}