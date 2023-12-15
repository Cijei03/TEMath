#include <chrono>
#include <iostream>

#include "../lib/headers/tem.hpp"

using namespace tem;

void Bench()
{
	std::cout << "Basic TEMath benchmark started." << std::endl;
	auto BenchStart = std::chrono::system_clock::now();

	f32mat4 m1 = f32mat4::unitMatrix();

	for (uint32_t i = 0; i < UINT16_MAX; i++)
	{
		m1.rotate(f32radian(f32degree(60.0f)), f32vec3(0.4f, 0.6f, 0.2f));
		m1 = m1 * f32mat4::unitMatrix();
	}

	std::chrono::milliseconds ElapsedTime = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - BenchStart);
	std::cout << "Benchmark finished in " << ElapsedTime.count() << "ms.\n" << std::endl;
}

TEM_AVX_SIMD void BenchAVX()
{
	std::cout << "TEMath benchmark with AVX usage started." << std::endl;
	auto BenchStart = std::chrono::system_clock::now();

	using f32mat4 = tem::avx::f32mat4;
	using f32vec3 = tem::avx::f32vec3;

	f32mat4 m1 = f32mat4::unitMatrix();
	f32mat4 m2 = f32mat4::unitMatrix();

	for (uint32_t i = 0; i < UINT16_MAX; i++)
	{
		m1.rotate(f32radian(f32degree(60.0f)), f32vec3(0.4f, 0.6f, 0.2f));
		m1 = m1 * m2;
	}

	std::chrono::milliseconds ElapsedTime = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - BenchStart);
	std::cout << "Benchmark finished in " << ElapsedTime.count() << "ms.\n" << std::endl;
}

TEM_AVX2_FMA3_SIMD void BenchAVX2()
{
	std::cout << "TEMath benchmark with AVX2 and FMA3 usage started." << std::endl;
	auto BenchStart = std::chrono::system_clock::now();

	using f32mat4 = tem::avx2::f32mat4;
	using f32vec3 = tem::avx2::f32vec3;

	f32mat4 m1 = f32mat4::unitMatrix();

	for (uint32_t i = 0; i < UINT16_MAX; i++)
	{
		m1.rotate(f32radian(f32degree(60.0f)), f32vec3(0.4f, 0.6f, 0.2f));
		m1 = m1 * f32mat4::unitMatrix();
	}

	std::chrono::milliseconds ElapsedTime = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - BenchStart);
	std::cout << "Benchmark finished in " << ElapsedTime.count() << "ms.\n" << std::endl;
}

int main()
{
	Bench();
	BenchAVX();
	BenchAVX2();

	return 0;
}