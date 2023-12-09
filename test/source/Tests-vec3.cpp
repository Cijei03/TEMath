#include "Tests-vec3.hpp"

#include "../../lib/headers/tem.hpp"

using namespace tem;

bool Vec3Test::Multiplication()
{
	f32vec3 m1(2, 1, 1);
	f32vec3 m2(2, 3, 3);

	auto result = m1 * m2;
	f32vec3 expectedResult(4, 3, 3);
	for (tem_ui32 i = 0; i < 2; i++)
	{
		if (result[i] != expectedResult[i])
			return false;
	}
	return true;
}
bool Vec3Test::Addition()
{
	f32vec3 m1(2, 1, 1);
	f32vec3 m2(2, 3, 3);

	auto result = m1 + m2;
	f32vec3 expectedResult(4, 4, 3);
	for (tem_ui8 i = 0; i < 2; i++)
	{
		if (result[i] != expectedResult[i])
			return false;
	}
	return true;
}
bool Vec3Test::Condition()
{
	f32vec3 m1(4, 5, 5);
	f32vec3 m2(6, 3, 3);

	bool result = m1 < m2;
	bool expectedResult = false;
	return (expectedResult == result);
}