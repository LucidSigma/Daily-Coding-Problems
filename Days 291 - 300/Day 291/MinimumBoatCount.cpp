#include <algorithm>
#include <cstddef>
#include <cstdlib>
#include <functional>
#include <iostream>
#include <iterator>
#include <stdexcept>
#include <vector>

static constexpr unsigned int BoatWeightLimit = 200u;

unsigned int GetMinBoatsHelper(std::vector<unsigned int> personWeights, const unsigned int boatCount)
{
	if (personWeights.size() < 2)
	{
		return boatCount + personWeights.size();
	}

	const unsigned int firstPersonWeight = personWeights.front();
	const std::vector<unsigned int> remainingPeople(std::cbegin(personWeights) + 1, std::cend(personWeights));

	if (firstPersonWeight > BoatWeightLimit)
	{
		throw std::invalid_argument("Single person's weight greater than boat weight limit.");
	}
	else if (firstPersonWeight == BoatWeightLimit)
	{
		return GetMinBoatsHelper(remainingPeople, boatCount + 1);
	}

	const unsigned int leftoverWeight = BoatWeightLimit - firstPersonWeight;
	size_t secondPersonIndex = remainingPeople.size() - 1;

	while (leftoverWeight >= personWeights[secondPersonIndex])
	{
		--secondPersonIndex;
	}

	if (secondPersonIndex == remainingPeople.size())
	{
		return GetMinBoatsHelper(remainingPeople, boatCount + 1);
	}

	personWeights.erase(std::cbegin(personWeights) + secondPersonIndex);

	return GetMinBoatsHelper(personWeights, boatCount + 1);
}

inline unsigned int GetMinBoats(std::vector<unsigned int> personWeights)
{
	std::sort(std::begin(personWeights), std::end(personWeights), std::greater<unsigned int>());

	return GetMinBoatsHelper(personWeights, 0);
}

int main(int argc, char* argv[])
{
	std::cout << GetMinBoats({ 100, 200, 150, 80 }) << "\n";

	std::cin.get();

	return EXIT_SUCCESS;
}