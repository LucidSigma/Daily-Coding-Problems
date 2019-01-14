#include <iostream>
#include <vector>

std::vector<int> GetProductArrayNoDivision(const std::vector<int>& numbers)
{
	const unsigned int SIZE = numbers.size();
	int productCounter = 1;
	std::vector<int> increasingProducts(SIZE);
	
	for (unsigned int i = 0; i < SIZE; i++)
	{
		increasingProducts[i] = productCounter;
		productCounter *= numbers[i];
	}

	productCounter = 1;
	std::vector<int> decreasingProducts(SIZE);

	for (int i = SIZE - 1; i >= 0; i--)
	{
		decreasingProducts[i] = productCounter;
		productCounter *= numbers[i];
	}

	std::vector<int> finalProducts(SIZE);

	for (unsigned int i = 0; i < SIZE; i++)
	{
		finalProducts[i] = increasingProducts[i] * decreasingProducts[i];
	}

	return finalProducts;
}

template <typename T>
void PrintVector(const std::vector<T>& vector)
{
	for (const T& item : vector)
	{
		std::cout << item << " ";
	}

	std::cout << "\n";
}

int main(int argc, char* argv[])
{
	std::vector<int> numbers { 1, 2, 3, 4, 5 };
	std::vector<int> moreNumbers { 3, 2, 1 };

	std::vector<int> numberProducts = GetProductArrayNoDivision(numbers);
	std::vector<int> moreNumberProducts = GetProductArrayNoDivision(moreNumbers);
	
	PrintVector(numberProducts);
	std::cout << "\n";
	PrintVector(moreNumberProducts);

	std::cin.get();

	return 0;
}
