#include <array>
#include <cstdlib>
#include <iostream>
#include <optional>
#include <stdexcept>

template <typename T, size_t Size>
class Queue
{
private:
	const size_t m_maxSize = Size;

	std::array<std::optional<T>, Size> m_fixedLengthArray;
	
	size_t m_size = 0;
	size_t m_startIndex = 0;
	size_t m_endIndex = 0;

public:
	Queue() = default;

	void Enqueue(const T& value)
	{
		if (m_size == m_maxSize)
		{
			throw std::runtime_error("Queue is full, cannot enqueue.");
		}

		m_fixedLengthArray[m_endIndex] = value;
		m_endIndex = (m_endIndex + 1) % m_maxSize;

		++m_size;
	}

	T Dequeue()
	{
		if (m_size == 0)
		{
			throw std::runtime_error("Queue is empty, cannot dequeue.");
		}

		const T dequeuedValue = m_fixedLengthArray[m_startIndex].value();
		m_fixedLengthArray[m_startIndex] = std::nullopt;
		m_startIndex = (m_startIndex + 1) % m_maxSize;

		--m_size;

		return dequeuedValue;
	}

	inline size_t GetSize() const noexcept { return m_size; }
};

int main(const int argc, const char* const argv[])
{
	Queue<unsigned int, 10> queue;

	for (unsigned int i = 1; i <= 5; ++i)
	{
		queue.Enqueue(i);
	}

	while (queue.GetSize() > 0)
	{
		std::cout << queue.Dequeue() << "\n";
	}

	std::cin.get();

	return EXIT_SUCCESS;
}