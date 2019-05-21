#include <initializer_list>
#include <iostream>
#include <iterator>
#include <memory>
#include <numeric>
#include <string>
#include <typeinfo>
#include <vector>

/*
	AD-HOC POLYMORPHISM
	A type of polymorphism where functions can have the same name but can be called with different parameters.
	Also known as function overloading or operator overloading.
*/

inline int Sum(int a, int b) noexcept
{
	return a + b;
}

inline int Sum(int a, int b, int c) noexcept
{
	return a + b + c;
}

inline float Sum(float a, float b) noexcept
{
	return a + b;
}

int Sum(const std::initializer_list<int>& numbers) noexcept
{
	return std::accumulate(std::cbegin(numbers), std::cend(numbers), 0);
}

/*
	PARAMETERIC POLYMORPHISM
	A type of polymorphism that makes use of generics or templates.
	This can be expressed by using type variables that are replaced when necessary.
*/

template <typename T>
void PrintType(const T&& value) noexcept
{
	std::cout << typeid(value).name() << "\n";
}

/*
	SUBTYPE POLYMORPHISM
	A type of polymorphism that determines which function to run from an inheritance tree.
	It is useful when only a supertype interface is given where the right function from a certain subtype is executed.
*/

class Shape
{
public:
	virtual float Area() const noexcept = 0;
};

class Square
	: public Shape
{
private:
	float length;

public:
	explicit Square(const float length) noexcept
		: length{ length }
	{ }

	virtual float Area() const noexcept override
	{
		return length * length;
	}
};

class Triangle
	: public Shape
{
private:
	float base;
	float height;

public:
	explicit Triangle(const float base, const float height) noexcept
		: base{ base }, height{ height }
	{ }

	virtual float Area() const noexcept override
	{
		return base * height / 2.0f;
	}
};

int main(int argc, char* argv[])
{
	using namespace std::literals::string_literals;

	// Ad-hoc polymorphism
	std::cout << Sum(1, 2) << "\n";
	std::cout << Sum(1, 2, 3) << "\n";
	std::cout << Sum(4.0f, 5.0f) << "\n";
	std::cout << Sum({ 1, 2, 3, 4, 5 }) << "\n\n";

	// Parametric polymorphism
	PrintType(15);
	PrintType(17.4);
	PrintType("polymorphism"s);
	PrintType(std::vector<int>{ 1, 2, 3 });

	std::cout << "\n";

	// Subtype polymorphism
	const std::vector<std::shared_ptr<Shape>> shapes{ std::make_shared<Square>(10.0f), std::make_shared<Triangle>(8.0f, 6.0f) };

	for (const auto& shape : shapes)
	{
		std::cout << shape->Area() << "\n";
	}

	std::cin.get();

	return 0;
}