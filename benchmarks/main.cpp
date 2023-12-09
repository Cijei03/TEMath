#include <chrono>
#include <iostream>

#include "../lib/headers/tem.hpp"

using namespace tem;

int Bench()
{
	f32mat4 m1 = f32mat4::unitMatrix();

	for (uint32_t i = 0; i < UINT16_MAX; i++)
	{
		m1.rotate(f32radian(f32degree(60.0f)), f32vec3(0.4f, 0.6f, 0.2f));
		m1 = m1 * f32mat4::unitMatrix();
	}

	return static_cast<int>(m1.getPtr()[0]);
}

int main()
{
	std::cout << "Benchmark started." << std::endl;
	auto BenchStart = std::chrono::system_clock::now();

	auto x = Bench();

	std::chrono::milliseconds ElapsedTime = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - BenchStart);
	std::cout << "Benchmark finished in " << ElapsedTime.count() << "ms." << x << std::endl;
	return 0;
}