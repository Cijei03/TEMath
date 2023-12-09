#include "Tests-vec4.hpp"

#include "../../lib/headers/tem.hpp"

using namespace tem;

bool Vec4Test::Multiplication()
{
	f32vec4 m1(2, 1, 1, 1);
	f32vec4 m2(2, 3, 3, 3);

	auto result = m1 * m2;
	f32vec4 expectedResult(4, 3, 3, 3);
	for (tem_ui32 i = 0; i < 2; i++)
	{
		if (result[i] != expectedResult[i])
			return false;
	}
	return true;
}
bool Vec4Test::Addition()
{
	f32vec4 m1(2, 1, 1, 1);
	f32vec4 m2(2, 3, 3, 3);

	auto result = m1 + m2;
	f32vec4 expectedResult(4, 4, 3, 3);
	for (tem_ui8 i = 0; i < 2; i++)
	{
		if (result[i] != expectedResult[i])
			return false;
	}
	return true;
}
bool Vec4Test::Condition()
{
	f32vec4 m1(4, 5, 5, 5);
	f32vec4 m2(6, 3, 3, 3);

	bool result = m1 < m2;
	bool expectedResult = false;
	return (expectedResult == result);
}