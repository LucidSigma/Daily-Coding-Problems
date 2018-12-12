#include <iostream>
#include <random>

double EstimatePiWithMonteCarlo(unsigned long iterations = 10'000l)
{
	constexpr double RADIUS = 0.5;
	constexpr double RADIUS_PI_RATIO = 1.0 / (RADIUS * RADIUS);

	static std::random_device randomSeed;
	static std::mt19937 randomEngine(randomSeed());
	static std::uniform_real_distribution<double> randomGenerator(-RADIUS, RADIUS);

	unsigned long innerCount = 0l;

	for (unsigned long i = 0l; i < iterations; i++)
	{
		double x = randomGenerator(randomEngine);
		double y = randomGenerator(randomEngine);

		if ((x * x + y * y) <= (RADIUS * RADIUS))
		{
			innerCount++;
		}
	}

	return RADIUS_PI_RATIO * (static_cast<double>(innerCount) / static_cast<double>(iterations));
}

int main(int argc, char* argv[])
{
	std::cout.precision(10);

	std::cout << EstimatePiWithMonteCarlo(10) << std::endl;
	std::cout << EstimatePiWithMonteCarlo(100) << std::endl;
	std::cout << EstimatePiWithMonteCarlo(1'000) << std::endl;
	std::cout << EstimatePiWithMonteCarlo(10'000) << std::endl;
	std::cout << EstimatePiWithMonteCarlo(100'000) << std::endl;
	std::cout << EstimatePiWithMonteCarlo(1'000'000) << std::endl;
	std::cout << EstimatePiWithMonteCarlo(10'000'000) << std::endl;
	std::cout << EstimatePiWithMonteCarlo(100'000'000) << std::endl;

	std::cin.get();

	return 0;
}
