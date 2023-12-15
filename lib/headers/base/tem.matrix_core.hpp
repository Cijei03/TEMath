#pragma once
#include <concepts>

namespace tem::intern
{
	template<typename T>
	concept MatrixCoreValidation = requires (T Matrix)
	{
		{ Matrix = Matrix + Matrix };
		{ Matrix = Matrix - Matrix };
		{ Matrix = Matrix * Matrix };
		{ Matrix.transpose() };
		{ Matrix.makeUnit() };
		{ Matrix.getDeterminant() };
		{ Matrix.inverse() };
	};
}