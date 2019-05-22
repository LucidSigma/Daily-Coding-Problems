#include <iostream>
#include <iterator>
#include <random>
#include <tuple>
#include <unordered_map>
#include <utility>
#include <vector>

using TransitionProbability = std::tuple<char, char, float>;
using TransitionMap = std::unordered_map<char, std::pair<std::vector<float>, std::vector<char>>>;

TransitionMap GetTransitionMap(const std::vector<TransitionProbability>& transitionProbabilities) noexcept
{
	TransitionMap transitionMap;

	for (const auto& [source, destination, probability] : transitionProbabilities)
	{
		if (transitionMap.find(source) == std::cend(transitionMap))
		{
			transitionMap[source] = { { }, { } };
		}

		if (transitionMap[source].first.empty())
		{
			transitionMap[source].first.push_back(probability);
		}
		else
		{
			const float previousProbability = transitionMap[source].first.back();
			transitionMap[source].first.push_back(previousProbability + probability);
		}

		transitionMap[source].second.push_back(destination);
	}

	return transitionMap;
}

char GetNextTraversal(const std::pair<std::vector<float>, std::vector<char>>& stateTransitionProbabilities) noexcept
{
	static std::random_device randomSeed;
	static std::mt19937 randomEngine(randomSeed());
	static std::uniform_real_distribution<float> randomRange(0.0f, 1.0f);

	const auto& [probabilities, states] = stateTransitionProbabilities;
	const float randomNumber = randomRange(randomEngine);
	unsigned int selectedStateIndex = 0;

	for (const auto& probability : probabilities)
	{
		if (probability > randomNumber)
		{
			break;
		}

		++selectedStateIndex;
	}

	return states[selectedStateIndex];
}

std::unordered_map<char, unsigned int> SimulateTraversals(const char start, const std::vector<TransitionProbability>& transitionProbabilities, const unsigned int stepCount) noexcept
{
	const TransitionMap transitionMap = GetTransitionMap(transitionProbabilities);
	std::unordered_map<char, unsigned int> traversalCounter;

	for (const auto& [state, _] : transitionMap)
	{
		traversalCounter[state] = 0;
	}

	char currentState = start;

	for (unsigned int i = 0; i < stepCount; ++i)
	{
		++traversalCounter[currentState];

		const auto currentStateTransitionProbability = transitionMap.at(currentState);
		currentState = GetNextTraversal(currentStateTransitionProbability);
	}

	return traversalCounter;
}

template <typename T, typename U>
std::ostream& operator <<(std::ostream& outputStream, const std::unordered_map<T, U>& values) noexcept
{
	for (const auto& [key, value] : values)
	{
		outputStream << "( " << key << ", " << value << " )\n";
	}

	return outputStream;
}

int main(int argc, char* argv[])
{
	const std::vector<TransitionProbability> transitionProbabilities
	{
		{ 'a', 'a', 0.9f },
		{ 'a', 'b', 0.075f },
		{ 'a', 'c', 0.025f },
		{ 'b', 'a', 0.15f },
		{ 'b', 'b', 0.8f },
		{ 'b', 'c', 0.05f },
		{ 'c', 'a', 0.25f },
		{ 'c', 'b', 0.25f },
		{ 'c', 'c', 0.5f }
	};

	std::cout << SimulateTraversals('a', transitionProbabilities, 5000) << "\n";

	std::cin.get();

	return 0;
}