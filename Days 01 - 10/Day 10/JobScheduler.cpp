#include <chrono>
#include <iostream>
#include <thread>
#include <type_traits>

template<typename Func, typename... Args, typename = std::enable_if_t<std::is_invocable_v<Func, Args...>>>
void ScheduleJob(Func function, unsigned int callbackMilliseconds, Args... params)
{
	std::this_thread::sleep_for(std::chrono::milliseconds(callbackMilliseconds));

	function(params...);
}

void JobA()
{
	std::cout << "Job A has been completed." << "\n";
}

void JobB(int a, int b)
{
	std::cout << "Job B completed with result of " << (a + b) << "." << "\n";
}

void JobC(const char* text, float a, float b)
{
	std::cout << text << "\n";
	std::cout << "Job C completed with result of " << (a + b) << "." << "\n";
}

int main(int argc, char* argv[])
{
	ScheduleJob(JobA, 1500);
	ScheduleJob(JobB, 500, 7, 4);
	ScheduleJob(JobC, 3250, "This will print.", 2.5f, 9.0f);

	std::cin.get();

	return 0;
}
