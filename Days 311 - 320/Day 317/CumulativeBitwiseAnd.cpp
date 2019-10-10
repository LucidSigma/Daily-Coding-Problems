#include <cmath>
#include <cstdlib>
#include <iostream>

inline int CumulativeBitwiseAnd(const int start, const int end)
{
	const int differenceLog = static_cast<int>(std::ceil(std::log2(end - start + 1)));
	const int endLog = static_cast<int>(std::ceil(std::log2(end)));

	return start & static_cast<int>(std::pow(2, endLog) - std::pow(2, differenceLog));
}

int main(const int argc, const char* const argv[])
{
	std::cout << CumulativeBitwiseAnd(128, 255) << "\n";

	std::cin.get();

	return EXIT_SUCCESS;
}