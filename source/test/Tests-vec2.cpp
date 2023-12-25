#include "Tests-vec2.hpp"

#include "../../include/tem.hpp"

using namespace tem;

bool Vec2Test::Multiplication()
{
	f32vec2 m1(2, 1);
	f32vec2 m2(2, 3);

	auto result = m1 * m2;
	f32vec2 expectedResult(4, 3);
	for (tem_ui32 i = 0; i < 2; i++)
	{
		if (result[i] != expectedResult[i])
			return false;
	}
	return true;
}
bool Vec2Test::Addition()
{
	f32vec2 m1(2, 1);
	f32vec2 m2(2, 3);

	auto result = m1 + m2;
	f32vec2 expectedResult(4, 4);
	for (tem_ui8 i = 0; i < 2; i++)
	{
		if (result[i] != expectedResult[i])
			return false;
	}
	return true;
}
bool Vec2Test::Condition()
{
	f32vec2 m1(4, 5);
	f32vec2 m2(6, 3);

	bool result = m1 < m2;
	bool expectedResult = false;
	return (expectedResult == result);
}