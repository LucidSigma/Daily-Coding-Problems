#include <algorithm>
#include <iostream>

struct Rectangle
{
	int x;
	int y;
	unsigned int w;
	unsigned int h;
};

unsigned int GetIntersectionArea(const Rectangle& rectA, const Rectangle& rectB) noexcept
{
	const int rectAX2 = rectA.x + static_cast<int>(rectA.w);
	const int rectAY2 = rectA.y + static_cast<int>(rectA.h);

	const int rectBX2 = rectB.x + static_cast<int>(rectB.w);
	const int rectBY2 = rectB.y + static_cast<int>(rectB.h);

	if (rectA.x < rectBX2 && rectAX2 > rectB.x && rectA.y > rectBY2 && rectAY2 < rectB.y)
	{
		return 0;
	}

	const int left = std::max(rectA.x, rectB.x);
	const int right = std::min(rectAX2, rectBX2);
	const int top = std::max(rectA.y, rectB.y);
	const int bottom = std::min(rectAY2, rectBY2);

	return (right - left) * (bottom - top);
}

int main(int argc, char* argv[])
{
	std::cout << GetIntersectionArea({ 1, 4, 3, 3 }, { 0, 5, 4, 3 }) << "\n";

	std::cin.get();

	return 0;
}