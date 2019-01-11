#include <iostream>
#include <string>
#include <utility>
#include <vector>

template <typename T>
std::string JoinVector(const std::vector<T>& values, const std::string& delimiter = "")
{
	std::string result;

	for (const auto& value : values)
	{
		result += value + delimiter;
	}

	return result;
}

std::vector<std::string> GetFlightItineraryHelper(const std::vector<std::pair<std::string, std::string>>& flights, const std::string& startingAirport, std::vector<std::string>& currentItinerary)
{
	if (flights.empty())
	{
		return currentItinerary.push_back(startingAirport), currentItinerary;
	}

	std::vector<std::string> itinerary;

	for (unsigned int i = 0; i < flights.size(); i++)
	{
		auto[startCity, endCity] = flights[i];

		if (startingAirport == startCity)
		{
			currentItinerary.push_back(startCity);

			std::vector<std::pair<std::string, std::string>> continuedFlights;

			for (unsigned int j = 0; j < flights.size(); j++)
			{
				if (j != i)
				{
					continuedFlights.push_back(flights[j]);
				}
			}

			std::vector<std::string> continuedItinerary = GetFlightItineraryHelper(continuedFlights, endCity, currentItinerary);

			if (!continuedItinerary.empty())
			{
				if (itinerary.empty() || (JoinVector(continuedItinerary) < JoinVector(itinerary)))
				{
					itinerary = continuedItinerary;
				}
			}
		}
	}

	return itinerary;
}

std::vector<std::string> GetFlightItinerary(const std::vector<std::pair<std::string, std::string>>& flights, const std::string& startingAirport)
{
	std::vector<std::string> itinerary;

	return GetFlightItineraryHelper(flights, startingAirport, itinerary);
}

template <typename T>
void PrintVector(const std::vector<T>& values)
{
	if (values.empty())
	{
		std::cout << "Vector is empty...\n";

		return;
	}

	for (const auto& value : values)
	{
		std::cout << value << " ";
	}

	std::cout << "\n";
}

int main(int argc, const char* argv[])
{
	std::vector<std::pair<std::string, std::string>> flights {
		{ "SFO", "HKO" },
		{ "YYZ", "SFO" },
		{ "YUL", "YYZ"},
		{ "HKO", "ORD" }
	};

	PrintVector(GetFlightItinerary(flights, "YUL"));

	flights = {
		{ "SFO", "COM" },
		{ "COM", "YYZ" }
	};

	PrintVector(GetFlightItinerary(flights, "COM"));

	flights = {
		{ "A", "B" },
		{ "A", "C" },
		{ "B", "C" },
		{ "C", "A" }
	};

	PrintVector(GetFlightItinerary(flights, "A"));

	std::cin.get();

	return 0;
}