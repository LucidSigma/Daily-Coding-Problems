#include <chrono>
#include <iostream>
#include <iterator>
#include <thread>
#include <vector>

using Timestamp = std::chrono::time_point<std::chrono::high_resolution_clock>;

struct TimestampFile
{
	static constexpr unsigned int TimestampsPerFile = 100u;

	Timestamp start = Timestamp::min();
	Timestamp end = Timestamp::min();

	std::vector<Timestamp> timestamps;

	void SaveToDisk() const noexcept
	{
		// In an actual application this would physically save the files to the disk in order to save memory
		return;
	}
};

class HitCounter
{
private:
	TimestampFile currentFile;
	std::vector<TimestampFile> previousFiles;

public:
	void Record(const Timestamp& timestamp) noexcept
	{
		if (currentFile.start == Timestamp::min())
		{
			currentFile.start = timestamp;
		}

		currentFile.timestamps.push_back(timestamp);
		currentFile.end = timestamp;

		if (currentFile.timestamps.size() == TimestampFile::TimestampsPerFile)
		{
			previousFiles.push_back(currentFile);
			currentFile = TimestampFile();
		}
	}

	inline unsigned int Total() const noexcept
	{
		return (previousFiles.size() * TimestampFile::TimestampsPerFile) + currentFile.timestamps.size();
	}

	unsigned int Range(const Timestamp& lower, const Timestamp& upper) const noexcept
	{
		auto allFiles = previousFiles;
		allFiles.push_back(currentFile);

		std::vector<Timestamp> startTimestamps;
		std::vector<Timestamp> endTimestamps;

		for (const auto& timestamp : allFiles)
		{
			startTimestamps.push_back(timestamp.start);
			endTimestamps.push_back(timestamp.end);
		}

		unsigned int startIndex = 0;
		
		for (unsigned int i = 0; i < startTimestamps.size(); i++)
		{
			if (startTimestamps[i] > lower)
			{
				startIndex = i == 0 ? i : i - 1;

				break;
			}
		}

		unsigned int endIndex = 0;

		for (unsigned int i = 0; i < endTimestamps.size(); i++)
		{
			if (endTimestamps[i] > upper)
			{
				endIndex = i;

				break;
			}
		}

		auto startFile = allFiles[startIndex];
		unsigned int startFileIndex = 0;

		for (unsigned int i = 0; i < startFile.timestamps.size(); i++)
		{
			if (startFile.timestamps[i] > lower)
			{
				startFileIndex = i == 0 ? i : i - 1;

				break;
			}
		}

		auto endFile = allFiles[endIndex];
		unsigned int endFileIndex = 0;

		for (unsigned int i = 0; i < endFile.timestamps.size(); i++)
		{
			if (endFile.timestamps[i] > upper)
			{
				endFileIndex = i;

				break;
			}
		}

		unsigned int numberInRange = 0;
		numberInRange += std::vector<Timestamp>(std::cbegin(startFile.timestamps) + startFileIndex, std::cend(startFile.timestamps)).size();
		numberInRange += std::vector<Timestamp>(std::cbegin(endFile.timestamps), std::cbegin(endFile.timestamps) + endFileIndex).size();
		numberInRange += (endIndex - startIndex) * TimestampFile::TimestampsPerFile;

		return numberInRange;
	}
};

int main(int argc, char* argv[])
{
	HitCounter hitCounter;

	static constexpr unsigned int LowerIndex = 459;
	static constexpr unsigned int UpperIndex = 6738;

	Timestamp lower;
	Timestamp upper;

	for (unsigned int i = 0; i < 10'000; i++)
	{
		using namespace std::literals::chrono_literals;

		hitCounter.Record(std::chrono::high_resolution_clock::now());

		switch (i)
		{
		case LowerIndex:
			lower = std::chrono::high_resolution_clock::now();

			break;

		case UpperIndex:
			upper = std::chrono::high_resolution_clock::now();

			break;

		default:
			break;
		}

		std::this_thread::sleep_for(1ms);
	}
	
	std::cout << hitCounter.Range(lower, upper) << "\n";

	std::cin.get();

	return 0;
}