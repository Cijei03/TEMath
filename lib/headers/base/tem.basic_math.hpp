#pragma once
#include "basic_preprocessor.hpp"
#include "tem.basic_types.hpp"

namespace tem
{
	template<intern::temType T>
	class BasicMath
	{
	public:
		static constexpr T PI = static_cast<T>(3.14159265358979323846);

		TEM_NODISCARD static constexpr T sqr(const T Value)
		{
			return T(Value * Value);
		}
		TEM_NODISCARD static constexpr T pow(const T Value, const tem_ui32 Power)
		{
			T Cache = Value;
			for (tem_ui32 i = 0; i < Power; i++)
			{
				Cache = Cache * Value;
			}
			return Cache;
		}
		TEM_NODISCARD static constexpr T clip(const T Min, const T Max, const T Value)
		{
			if (Value < Min) return Min;
			else if (Value > Max) return Max;
			return Value;
		}
	};

	using f32BasicMath = BasicMath<tem_f32>;
	using f64BasicMath = BasicMath<tem_f64>;

	using i8BasicMath = BasicMath<tem_i8>;
	using i16BasicMath = BasicMath<tem_i16>;
	using i32BasicMath = BasicMath<tem_i32>;
	using i64BasicMath = BasicMath<tem_i64>;

	using ui8BasicMath = BasicMath<tem_ui8>;
	using ui16BasicMath = BasicMath<tem_ui16>;
	using ui32BasicMath = BasicMath<tem_ui32>;
	using ui64BasicMath = BasicMath<tem_ui64>;
};