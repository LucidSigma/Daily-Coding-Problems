#include <cstdlib>
#include <iostream>
#include <stack>
#include <stdexcept>

template <typename T>
class Quack
{
private:
	std::stack<T> m_leftStack;
	std::stack<T> m_rightStack;

	std::stack<T> m_placeholderStack;

public:
	Quack() = default;
	~Quack() noexcept = default;

	void Push(const T& value)
	{
		m_leftStack.push(value);
	}

	T Pop()
	{
		if (!m_leftStack.empty())
		{
			const auto poppedValue = m_leftStack.top();
			m_leftStack.pop();

			return poppedValue;
		}
		else if (!m_rightStack.empty())
		{
			return PopBottomOfStack(m_rightStack);
		}
		else
		{
			throw std::runtime_error("Quack is empty when popped.");
		}
	}

	T Pull()
	{
		if (!m_rightStack.empty())
		{
			return PopBottomOfStack(m_rightStack);
		}
		else if (!m_leftStack.empty())
		{
			return PopBottomOfStack(m_leftStack);
		}
		else
		{
			throw std::runtime_error("Quack is empty when pulled.");
		}
	}

private:
	T PopBottomOfStack(std::stack<T>& stack)
	{
		while (!stack.empty())
		{
			m_placeholderStack.push(stack.top());
			stack.pop();
		}

		const auto poppedValue = m_placeholderStack.top();
		m_placeholderStack.pop();

		while (!m_placeholderStack.empty())
		{
			stack.push(m_placeholderStack.top());
			m_placeholderStack.pop();
		}

		return poppedValue;
	}
};

int main(const int argc, const char* const argv[])
{
	Quack<int> quack;

	for (unsigned int i = 0; i < 5; ++i)
	{
		quack.Push(i);
	}

	std::cout << quack.Pop() << "\n";
	std::cout << quack.Pop() << "\n";
	std::cout << quack.Pull() << "\n";

	std::cin.get();

	return EXIT_SUCCESS;
}