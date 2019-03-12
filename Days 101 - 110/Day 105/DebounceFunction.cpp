#include <chrono>
#include <functional>
#include <iostream>
#include <limits>
#include <optional>
#include <thread>
#include <type_traits>
#include <utility>

template <typename Func, typename... Args, typename = std::enable_if_t<std::is_invocable_v<Func, Args...>>>
auto DebounceFunction(Func function, const unsigned int milliseconds, Args&&... parameters) noexcept(noexcept(function)) -> std::optional<decltype(function(parameters...))>
{
	static bool firstRun = true;
	static std::chrono::time_point previousDebounceTime = std::chrono::high_resolution_clock::time_point::min();

	std::chrono::milliseconds difference(std::numeric_limits<long long>::max());

	if (!firstRun)
	{
		const std::chrono::time_point currentTime = std::chrono::high_resolution_clock::now();
		difference = std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - previousDebounceTime);
	}
	else
	{
		firstRun = false;
	}

	if (difference > std::chrono::milliseconds(milliseconds))
	{
		previousDebounceTime = std::chrono::high_resolution_clock::now();

		return function(std::forward<Args>(parameters)...);
	}

	return std::nullopt;
}

int TestFunction(int a, int b) noexcept
{
	return a + b;
}

int main(int argc, char* argv[])
{
	using namespace std::literals::chrono_literals;

	std::cout << DebounceFunction(TestFunction, 2500, 3, 5).value() << "\n";

	std::this_thread::sleep_for(1s);

	if (!DebounceFunction(TestFunction, 2500, 4, 6).has_value())
	{
		std::cout << "Hasn't debounced yet.\n";
	}

	std::this_thread::sleep_for(2s);

	std::cout << DebounceFunction(TestFunction, 2500, 2, 9).value() << "\n";

	std::cin.get();

	return 0;
}