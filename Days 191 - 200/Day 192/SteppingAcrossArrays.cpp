#include <array>
#include <cstddef>
#include <iostream>

template <std::size_t Size>
bool CanStepAcrossArrayHelper(const std::array<unsigned int, Size>& array, const std::size_t currentIndex) noexcept
{
	if (currentIndex >= Size - 1)
	{
		return true;
	}

	for (unsigned int i = 1; i <= array[currentIndex]; ++i)
	{
		if (CanStepAcrossArrayHelper(array, currentIndex + i))
		{
			return true;
		}
	}

	return false;
}

template <std::size_t Size>
inline bool CanStepAcrossArray(const std::array<unsigned int, Size>& array) noexcept
{
	return CanStepAcrossArrayHelper(array, 0);
}

int main(int argc, char* argv[])
{
	std::cout << std::boolalpha;
	std::cout << CanStepAcrossArray<6>({ 1, 3, 1, 2, 0, 1 }) << "\n";
	std::cout << CanStepAcrossArray<5>({ 1, 2, 1, 0, 0 }) << "\n";

	std::cin.get();

	return 0;
}