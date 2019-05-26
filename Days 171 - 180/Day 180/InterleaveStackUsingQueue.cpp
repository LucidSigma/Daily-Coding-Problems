#include <iostream>
#include <queue>
#include <stack>

void InterleaveStackHelper(std::stack<int>& stack, std::queue<int>& queue, const unsigned int currentIndex) noexcept
{
	const unsigned int originalStackSize = stack.size();

	for (unsigned int i = 0; i < originalStackSize - currentIndex; ++i)
	{
		queue.push(stack.top());
		stack.pop();
	}

	while (!queue.empty())
	{
		stack.push(queue.front());
		queue.pop();
	}

	if (stack.size() - currentIndex > 1)
	{
		InterleaveStackHelper(stack, queue, currentIndex + 1);
	}
}

inline void InterleaveStack(std::stack<int>& stack) noexcept
{
	std::queue<int> helperQueue;

	return InterleaveStackHelper(stack, helperQueue, 1);
}

std::ostream& operator <<(std::ostream& outputStream, std::stack<int> stack) noexcept
{
	while (!stack.empty())
	{
		outputStream << stack.top() << " ";

		stack.pop();
	}
	
	return outputStream;
}

int main(int argc, char* argv[])
{
	std::stack<int> stack;

	for (unsigned int i = 1; i <= 5; ++i)
	{
		stack.push(i);
	}

	std::cout << "Before interleave: " << stack << "\n";

	InterleaveStack(stack);

	std::cout << " After interleave: " << stack << "\n\n";

	std::stack<int> stack2;

	for (unsigned int i = 1; i <= 4; ++i)
	{
		stack2.push(i);
	}

	std::cout << "Before interleave: " << stack2 << "\n";

	InterleaveStack(stack2);

	std::cout << " After interleave: " << stack2 << "\n";

	std::cin.get();

	return 0;
}
