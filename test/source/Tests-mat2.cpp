#include "Tests-mat2.hpp"

#include "../../lib/headers/tem.hpp"

using namespace tem;

bool Mat2Test::Multiplication()
{
	f32mat2 m1(f32vec2(2, 1), f32vec2(3, 4));
	f32mat2 m2(f32vec2(2, 1), f32vec2(1, 2));

	auto result = m1 * m2;
	f32mat2 expectedResult(f32vec2(5, 4), f32vec2(10, 11));
	for (tem_ui32 i = 0; i < 4; i++)
	{
		if (result.getPtr()[i] != expectedResult.getPtr()[i])
			return false;
	}
	return true;
}
bool Mat2Test::Addition()
{
	f32mat2 m1(f32vec2(2, 1), f32vec2(3, 4));
	f32mat2 m2(f32vec2(2, 1), f32vec2(1, 2));

	auto result = m1 + m2;
	f32mat2 expectedResult(f32vec2(4, 2), f32vec2(4, 6));
	for (tem_ui8 i = 0; i < 4; i++)
	{
		if (result.getPtr()[i] != expectedResult.getPtr()[i])
			return false;
	}
	return true;
}
bool Mat2Test::VectorMultiplication()
{
	f32mat2 m1(f32vec2(2, 1), f32vec2(3, 4));
	f32vec2 v1(2, 1);

	auto result = m1 * v1;
	f32vec2 expectedResult(5, 10);
	return (expectedResult == result);
}

bool Mat2Test::MatrixDeterminant()
{
	i32mat2 m1(i32vec2(-3, 5), i32vec2(-4, 2));
	return m1.getDeterminant() == 14;
}

bool Mat2Test::MatrixInverse()
{
	i32mat2 m1(i32vec2(2, 1), i32vec2(5, 3));

	auto result = m1.inverse();
	i32mat2 expectedResult(i32vec2(3, -1), i32vec2(-5, 2));

	for (tem_ui8 i = 0; i < 4; i++)
	{
		if (result.getPtr()[i] != expectedResult.getPtr()[i])
		{
			return false;
		}
	}
	return true;
}

bool Mat2Test::MatrixTranspose()
{
	i32mat2 m1(i32vec2(1, 1), i32vec2(2, 2));

	const i32mat2 expectedResult(i32vec2(1, 2), i32vec2(1, 2));
	auto result = m1.transpose();

	for (tem_ui8 i = 0; i < 4; i++)
	{
		if (result.getPtr()[i] != expectedResult.getPtr()[i])
		{
			return false;
		}
	}
	return true;
}