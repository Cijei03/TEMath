#include "Tests-mat4.hpp"

#include "../../include/tem.hpp"

using namespace tem;

bool Mat4Test::Multiplication()
{
	f32mat4 m1(f32vec4(2, 1, 0, 2), f32vec4(2, 1, 0, 2), f32vec4(2, 1, 0, 2), f32vec4(2, 1, 0, 2));
	f32mat4 m2(f32vec4(2, 1, 0, 2), f32vec4(2, 1, 0, 2), f32vec4(2, 1, 0, 2), f32vec4(2, 1, 0, 2));

	auto result = m1 * m2;
	f32mat4 expectedResult(f32vec4(10, 5, 0, 10), f32vec4(10, 5, 0, 10), f32vec4(10, 5, 0, 10), f32vec4(10, 5, 0, 10));
	for (tem_ui32 i = 0; i < 16; i++)
	{
		if (result.getPtr()[i] != expectedResult.getPtr()[i])
			return false;
	}
	return true;
}
bool Mat4Test::Addition()
{
	f32mat4 m1(f32vec4(2, 1, 0, 2), f32vec4(2, 1, 0, 2), f32vec4(2, 1, 0, 2), f32vec4(2, 1, 0, 2));
	f32mat4 m2(f32vec4(2, 1, 0, 2), f32vec4(2, 1, 0, 2), f32vec4(2, 1, 0, 2), f32vec4(2, 1, 0, 2));

	auto result = m1 + m2;
	f32mat4 expectedResult(
		f32vec4(4, 2, 0, 4),
		f32vec4(4, 2, 0, 4),
		f32vec4(4, 2, 0, 4),
		f32vec4(4, 2, 0, 4)
	);
	for (tem_ui32 i = 0; i < 16; i++)
	{
		if (result.getPtr()[i] != expectedResult.getPtr()[i])
			return false;
	}
	return true;
}
bool Mat4Test::VectorMultiplication()
{
	f32mat4 m1(f32vec4(2, 1, 0, 2), f32vec4(2, 1, 0, 2), f32vec4(2, 1, 0, 2), f32vec4(2, 1, 0, 2));
	f32vec4 v1(2, 1, 1, 1);

	auto result = m1 * v1;
	f32vec4 expectedResult(7, 7, 7, 7);
	return (expectedResult == result);
}

bool Mat4Test::MatrixDeterminant()
{
	i32mat4 m1(
		i32vec4(3, 1, 3, 2),
		i32vec4(2, 2, 3, 2),
		i32vec4(9, 1, 3, 7),
		i32vec4(2, 1, 3, 1)
	);
	return m1.getDeterminant() == 3;
}

bool Mat4Test::MatrixInverse()
{
	i32mat4 m1(
		i32vec4(3, 1, 3, 2),
		i32vec4(2, 2, 3, 2),
		i32vec4(9, 1, 3, 7),
		i32vec4(2, 1, 3, 1)
	);

	auto result = m1.inverse();

	i32mat4 expectedResult(
		i32vec4(-6, 0, 1, 5),
		i32vec4(-7, 1, 1, 5),
		i32vec4(4, 0, 0, 0),
		i32vec4(7, 0, -1, -6)
	);

	for (tem_ui8 i = 0; i < 8; i++)
	{
		if (result.getPtr()[i] != expectedResult.getPtr()[i])
		{
			return false;
		}
	}

	return true;
}

bool Mat4Test::MatrixTranspose()
{
	i32mat4 m1(
		i32vec4(1, 1, 1, 1),
		i32vec4(2, 2, 2, 2),
		i32vec4(3, 3, 3, 3),
		i32vec4(4, 4, 4, 4)
	);
	auto result = m1.transpose();

	const i32mat4 expectedResult(
		i32vec4(1, 2, 3, 4),
		i32vec4(1, 2, 3, 4),
		i32vec4(1, 2, 3, 4),
		i32vec4(1, 2, 3, 4)
	);

	for (tem_ui8 i = 0; i < 16; i++)
	{
		if (result.getPtr()[i] != expectedResult.getPtr()[i])
		{
			return false;
		}
	}
	return true;
}