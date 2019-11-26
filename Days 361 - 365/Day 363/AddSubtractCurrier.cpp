#include <cstdlib>
#include <iostream>

class AddSubtractCurrier
{
private:
	int m_value;
	bool m_addNumber = true;

public:
	inline explicit AddSubtractCurrier(const int value)
		: m_value(value)
	{ }

	~AddSubtractCurrier() noexcept = default;

	AddSubtractCurrier& operator ()(const int value)
	{
		m_value += m_addNumber ? value : -value;
		m_addNumber = !m_addNumber;

		return *this;
	}

	inline operator int() const noexcept { return m_value; }
};

inline AddSubtractCurrier AddSubtract(const int value)
{
	return AddSubtractCurrier(value);
}

int main(const int argc, const char* const argv[])
{
	std::cout << AddSubtract(7) << "\n";
	std::cout << AddSubtract(1)(2)(3) << "\n";
	std::cout << AddSubtract(-5)(10)(3)(9) << "\n";

	std::cin.get();

	return EXIT_SUCCESS;
}