#include <cmath>
#include <cstdlib>
#include <iostream>
#include <string>

inline float GetHourAngle(const unsigned int hour, const unsigned int minute)
{
	const float minuteOffset = static_cast<float>(minute) / 12.0f;
	
	return (hour * 30.0f) + minuteOffset;
}

inline float GetMinuteAngle(const unsigned int minute)
{
	return minute * 6.0f;
}

float GetAngleBetweenHands(const std::string& hhmm)
{
	const unsigned int hour = std::stoul(hhmm.substr(0, 2)) % 12;
	const unsigned int minute = std::stoul(hhmm.substr(3));

	const float hourAngle = GetHourAngle(hour, minute);
	const float minuteAngle = GetMinuteAngle(minute);

	const float angleDifference = std::abs(hourAngle - minuteAngle);

	return angleDifference < 180.0f ? angleDifference : 360.0f - angleDifference;
}

int main(const int argc, const char* const argv[])
{
	std::cout << GetAngleBetweenHands("12:30") << "\n";
	std::cout << GetAngleBetweenHands("05:45") << "\n";
	std::cout << GetAngleBetweenHands("15:00") << "\n";
	std::cout << GetAngleBetweenHands("17:48") << "\n";
	std::cout << GetAngleBetweenHands("12:00") << "\n";

	std::cin.get();

	return EXIT_SUCCESS;
}