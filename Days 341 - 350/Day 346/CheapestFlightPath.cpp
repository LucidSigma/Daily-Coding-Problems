#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <iterator>
#include <limits>
#include <string>
#include <tuple>
#include <unordered_map>
#include <utility>
#include <vector>

using Flight = std::tuple<std::string, std::string, unsigned int>;
using CityGraph = std::unordered_map<std::string, std::vector<std::pair<std::string, unsigned int>>>;

inline bool operator <(const std::pair<unsigned int, std::vector<std::string>>& lhs, const std::pair<unsigned int, std::vector<std::string>>& rhs) noexcept
{
	return lhs.first < rhs.first;
}

CityGraph CreateCityGraph(const std::vector<Flight>& flights)
{
	CityGraph cityGraph;

	for (const auto& [source, destination, price] : flights)
	{
		if (cityGraph.find(destination) == std::cend(cityGraph))
		{
			cityGraph[destination] = { };
		}

		cityGraph[destination].emplace_back(source, price);
	}

	return cityGraph;
}

std::pair<unsigned int, std::vector<std::string>> GetCheapestFlightFareHelper(const std::string& startingCity, const std::string& destinationCity, const unsigned int maxFlights, const CityGraph& cityGraph, const std::vector<std::string>& reverseflightPath, const unsigned int totalCost, const unsigned int flightCount)
{
	if (flightCount > maxFlights)
	{
		return { std::numeric_limits<unsigned int>::max(), { } };
	}

	if (startingCity == destinationCity)
	{
		return { totalCost, reverseflightPath };
	}
	
	const auto& nextDestinations = cityGraph.at(destinationCity);
	std::vector<std::pair<unsigned int, std::vector<std::string>>> candidateFlightPaths;

	for (const auto& [nextDestination, price] : nextDestinations)
	{
		auto newFlightPath = reverseflightPath;
		newFlightPath.push_back(nextDestination);

		candidateFlightPaths.push_back(GetCheapestFlightFareHelper(startingCity, nextDestination, maxFlights, cityGraph, newFlightPath, totalCost + price, flightCount + 1));
	}

	return *std::min_element(std::cbegin(candidateFlightPaths), std::cend(candidateFlightPaths));
}

inline std::pair<unsigned int, std::vector<std::string>> GetCheapestFlightFare(const std::string& startingCity, const std::string& destinationCity, const unsigned int maxFlights, const std::vector<Flight>& flights)
{
	auto result = GetCheapestFlightFareHelper(startingCity, destinationCity, maxFlights, CreateCityGraph(flights), { destinationCity }, 0, 0);
	std::reverse(std::begin(result.second), std::end(result.second));

	return result;
}

template <typename T>
std::ostream& operator <<(std::ostream& outputStream, const std::vector<T>& values)
{
	for (const auto& value : values)
	{
		outputStream << value << " ";
	}

	return outputStream;
}

int main(const int argc, const char* const argv[])
{
	std::vector<Flight> flights
	{
		{ "JFK", "ATL", 150 },
		{ "ATL", "SFO", 400 },
		{ "ORD", "LAX", 200 },
		{ "LAX", "DFW", 80 },
		{ "JFK", "HKG", 800 },
		{ "ATL", "ORD", 90 },
		{ "JFK", "LAX", 500 }
	};

	const auto [price, path] = GetCheapestFlightFare("JFK", "LAX", 3, flights);
	
	std::cout << "Minimum price is " << price << ", with the following flight chain:\n";
	std::cout << path << "\n";

	std::cin.get();

	return EXIT_SUCCESS;
}