#include "Tests-mat3.hpp"

#include "../../include/tem.hpp"

using namespace tem;

bool Mat3Test::Multiplication()
{
	f32mat3 m1(f32vec3(2, 1, 0), f32vec3(3, 4, 1), f32vec3(5, 2, 4));
	f32mat3 m2(f32vec3(2, 1, 1), f32vec3(1, 2, 5), f32vec3(3, 3, 8));

	auto result = m1 * m2;
	f32mat3 expectedResult(f32vec3(5, 4, 7), f32vec3(13, 14, 31), f32vec3(24, 21, 47));
	for (tem_ui32 i = 0; i < 9; i++)
	{
		if (result.getPtr()[i] != expectedResult.getPtr()[i])
			return false;
	}
	return true;
}
bool Mat3Test::Addition()
{
	f32mat3 m1(f32vec3(2, 1, 0), f32vec3(3, 4, 1), f32vec3(5, 2, 4));
	f32mat3 m2(f32vec3(2, 1, 1), f32vec3(1, 2, 5), f32vec3(3, 3, 8));

	auto result = m1 + m2;
	f32mat3 expectedResult(f32vec3(4, 2, 1), f32vec3(4, 6, 6), f32vec3(8, 5, 12));
	for (tem_ui32 i = 0; i < 9; i++)
	{
		if (result.getPtr()[i] != expectedResult.getPtr()[i])
			return false;
	}
	return true;
}
bool Mat3Test::VectorMultiplication()
{
	f32mat3 m1(f32vec3(2, 1, 0), f32vec3(3, 4, 1), f32vec3(5, 2, 4));
	f32vec3 v1(2, 1, 1);

	auto result = m1 * v1;
	f32vec3 expectedResult(5, 11, 16);
	return (expectedResult == result);
}

bool Mat3Test::MatrixDeterminant()
{
	i32mat3 m1(i32vec3(2, 1, 0), i32vec3(3, 4, 1), i32vec3(5, 2, 4));
	return m1.getDeterminant() == 21;
}

bool Mat3Test::MatrixInverse()
{
	i32mat3 m1(i32vec3(2, 1, 0), i32vec3(2, 2, 1), i32vec3(1, 1, 4));

	auto result = m1.inverse();
	//i32mat3 expectedResult(i32vec3(3, -1), i32vec3(-5, 2));
	i32vec2 res(1, -1);

	return result[0][0] == 1 && result[1][0] == -1;

	//for (tem_ui8 i = 0; i < 4; i++)
	{
		//if (result.getPtr()[i] != expectedResult.getPtr()[i])
		{
			//return false;
		}
	}
	return true;
}

bool Mat3Test::MatrixTranspose()
{
	i32mat3 m1(i32vec3(1, 3, 4), i32vec3(1, 3, 4), i32vec3(1, 3, 4));
	auto result = m1.transpose();

	const i32mat3 expectedResult(i32vec3(1, 1, 1), i32vec3(3, 3, 3), i32vec3(4, 4, 4));

	for (tem_ui8 i = 0; i < 9; i++)
	{
		if (result.getPtr()[i] != expectedResult.getPtr()[i])
		{
			return false;
		}
	}
	return true;
}