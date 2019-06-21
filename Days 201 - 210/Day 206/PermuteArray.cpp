#include <array>
#include <cstddef>
#include <iostream>

template <typename T, std::size_t Size>
std::array<T, Size> PermuteArray(const std::array<T, Size>& array, const std::array<std::size_t, Size>& permutationIndices)
{
	std::array<T, Size> permutatedArray;

	for (std::size_t i = 0; i < Size; ++i)
	{
		permutatedArray[i] = array[permutationIndices[i]];
	}

	return permutatedArray;
}

template <typename T, std::size_t Size>
std::ostream& operator <<(std::ostream& outputStream, const std::array<T, Size>& array) noexcept
{
	outputStream << "[ ";

	for (const auto& value : array)
	{
		outputStream << value << " ";
	}

	outputStream << "]";

	return outputStream;
}

int main(int argc, char* argv[])
{
	std::cout << PermuteArray<char, 3>({ 'a', 'b', 'c' }, { 2, 1, 0 }) << "\n";

	std::cin.get();

	return 0;
}