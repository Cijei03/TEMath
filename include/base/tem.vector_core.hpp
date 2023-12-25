#pragma once
#include <concepts>

namespace tem::intern
{
	template<typename T>
	concept VectorCoreValidation = requires (T Vector)
	{
		{ Vector.abs() };
		{ Vector.normalize() };
		{ Vector.length() };

		{ T::dot(T(5), T(5)) };
		{ T::distance(T(5), T(5)) };

		{ Vector = Vector + T(5) };
		{ Vector += T(5) };
		{ Vector = Vector * T(5) };
		{ Vector *= T(5) };
		{ Vector = Vector - T(5) };
		{ Vector -= T(5) };
		{ Vector = Vector / T(5) };
		{ Vector /= T(5) };
	};
}