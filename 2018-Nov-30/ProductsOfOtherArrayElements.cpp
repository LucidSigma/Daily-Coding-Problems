#include <iostream>
#include <tuple>
#include <type_traits>
#include <vector>

// With division
template<typename T, typename = typename std::enable_if<std::is_arithmetic<T>::value>::type>
std::vector<T> GetProductArrayDivision(const std::vector<T>& numbers)
{
	int finalProduct = 1;

	for (T number : numbers)
	{
		finalProduct *= number;
	}

	std::vector<T> finalProducts(numbers.size());

	for (unsigned int i = 0; i < finalProducts.size(); i++)
	{
		finalProducts[i] = finalProduct;
		finalProducts[i] /= numbers[i];
	}

	return finalProducts;
}

// Alternate division solution (very optimal)
template<typename... Numbers>
std::vector<int> GetProductArrayVariadic(Numbers... numbers)
{
	int totalProduct = (numbers * ...);
	std::vector<int> products { numbers... };

	for (unsigned int i = 0; i < products.size(); i++)
	{
		products[i] = totalProduct / products[i];
	}

	return products;
}

// Without division
template<typename T, typename = typename std::enable_if<std::is_arithmetic<T>::value>::type>
std::vector<T> GetProductArrayNoDivision(const std::vector<T>& numbers)
{
	const unsigned int SIZE = numbers.size();
	int productCounter = 1;
	std::vector<T> increasingProducts(SIZE);
	
	for (unsigned int i = 0; i < SIZE; i++)
	{
		increasingProducts[i] = productCounter;
		productCounter *= numbers[i];
	}

	productCounter = 1;
	std::vector<T> decreasingProducts(SIZE);

	for (int i = SIZE - 1; i >= 0; i--)
	{
		decreasingProducts[i] = productCounter;
		productCounter *= numbers[i];
	}

	std::vector<T> finalProducts(SIZE);

	for (unsigned int i = 0; i < SIZE; i++)
	{
		finalProducts[i] = increasingProducts[i] * decreasingProducts[i];
	}

	return finalProducts;
}

template<typename T>
void PrintVector(const std::vector<T>& vector)
{
	for (const T& item : vector)
	{
		std::cout << item << " ";
	}

	std::cout << std::endl;
}

int main(int argc, char* argv[])
{
	std::vector<int> numbers {  6, 5, 9, 2, 7, 1 };
	std::vector<int> numberProductsDivision = GetProductArrayDivision(numbers);
	std::vector<int> numberProductsNoDivision = GetProductArrayNoDivision(numbers);
	std::vector<int> numberProductsVariadic = GetProductArrayVariadic(6, 5, 9, 2, 7, 1);

	PrintVector(numberProductsDivision);
	PrintVector(numberProductsNoDivision);
	PrintVector(numberProductsVariadic);

	std::cin.get();

	return 0;
}