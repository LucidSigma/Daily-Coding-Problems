using System;
using System.Collections.Generic;

namespace DailyCodingProblem
{
	internal class Day41
	{
		private static int Main(string[] args)
		{
			List<(string, string)> flights = new List<(string, string)>()
			{
				("SFO", "HKO"),
				("YYZ", "SFO"),
				("YUL", "YYZ"),
				("HKO", "ORD")
			};

			PrintList(GetFlightItinerary(flights, "YUL"));

			flights = new List<(string, string)>()
			{
				("SFO", "COM"),
				("COM", "YYZ")
			};

			PrintList(GetFlightItinerary(flights, "COM"));

			Console.ReadLine();

			return 0;
		}

		private static List<string> GetFlightItinerary(List<(string, string)> flights, string startingAirport)
		{
			List<string> itinerary = new List<string>();

			return GetFlightItineraryHelper(flights, startingAirport, itinerary);
		}

		private static List<string> GetFlightItineraryHelper(List<(string, string)> flights, string startingAirport, List<string> currentItinerary)
		{
			if (flights.Count == 0)
			{
				currentItinerary.Add(startingAirport);
				return currentItinerary;
			}

			List<string> itinerary = new List<string>();

			for (int i = 0; i < flights.Count; i++)
			{
				(string startCity, string endCity) = flights[i];

				if (startingAirport == startCity)
				{
					currentItinerary.Add(startCity);
					List<(string, string)> continuedFlights = new List<(string, string)>();

					for (int j = 0; j < flights.Count; j++)
					{
						if (j != i)
						{
							continuedFlights.Add(flights[j]);
						}
					}

					List<string> continuedItinerary = GetFlightItineraryHelper(continuedFlights, endCity, currentItinerary);

					if (continuedItinerary.Count > 0)
					{
						if (itinerary.Count == 0 || string.Compare(JoinListAsString(continuedItinerary), JoinListAsString(itinerary)) < 0)
						{
							itinerary = continuedItinerary;
						}
					}
				}
			}

			return itinerary;
		}

		private static string JoinListAsString<T>(List<T> values, string delimiter = "") => string.Join(delimiter, values.ToArray());

		private static void PrintList<T>(List<T> values)
		{
			if (values.Count == 0)
			{
				Console.WriteLine("List is empty...");

				return;
			}

			foreach (T value in values)
			{
				Console.Write($"{value} ");
			}

			Console.WriteLine();
		}
	}
}