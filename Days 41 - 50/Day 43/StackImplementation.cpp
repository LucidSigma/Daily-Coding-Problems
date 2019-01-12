#include <iostream>
#include <stdexcept>
#include <vector>

template <typename T>
class Stack
{
private:
	std::vector<T> data;
	std::vector<T> maximums;

public:
	Stack() = default;

	void Push(T value)
	{
		data.push_back(value);

		if (maximums.empty() || (value > data[maximums.back()]))
		{
			maximums.push_back(data.size() - 1);
		}
	}

	T Pop()
	{
		if (data.empty())
		{
			throw std::runtime_error("No data to remove from stack.");
		}

		if (data.size() - 1 == maximums.back())
		{
			maximums.pop_back();
		}

		T poppedValue = data.back();

		return data.pop_back(), poppedValue;
	}

	T Max() const
	{
		if (data.empty())
		{
			throw std::runtime_error("Stack is empty.");
		}

		return data[maximums.back()];
	}
};

int main(int argc, const char* argv[])
{
	Stack<int> stack;

	stack.Push(3);
	stack.Push(1);
	stack.Push(4);
	stack.Push(5);
	stack.Push(2);

	std::cout << stack.Max() << "\n";

	stack.Pop();
	stack.Pop();

	std::cout << stack.Max() << "\n";

	stack.Pop();

	std::cout << stack.Max() << "\n";

	std::cin.get();

	return 0;
}