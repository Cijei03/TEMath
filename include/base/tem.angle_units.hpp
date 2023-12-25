#pragma once
#include "basic_preprocessor.hpp"
#include <concepts>
#include "tem.basic_types.hpp"
#include "tem.basic_math.hpp"

namespace tem
{
	template<intern::temType T>
	class Degree;

	template<intern::temType T>
	class Radian
	{
	protected:
		T Value;
	public:
		explicit constexpr Radian(const T value)
		{
			this->Value = value;
		}
		explicit constexpr Radian(const Degree<T> value)
		{
			this->Value = T(value) * (BasicMath<T>::PI / static_cast<T>(180.0));
		}

		TEM_NODISCARD explicit constexpr operator T() const
		{
			return T(this->Value);
		}
		TEM_NODISCARD explicit constexpr operator Degree<T>() const
		{
			return Degree<T>(*this);
		}
	};

	template<intern::temType T>
	class Degree
	{
	protected:
		T Value;
	public:
		explicit constexpr Degree(const T value)
		{
			this->Value = value;
		}
		explicit constexpr Degree(const Radian<T> value)
		{
			this->Value = T(value) * (static_cast<T>(180.0) / BasicMath<T>::PI);
		}

		TEM_NODISCARD explicit constexpr operator T() const
		{
			return T(this->Value);
		}
		TEM_NODISCARD explicit constexpr operator Radian<T>() const
		{
			return Radian<T>(*this);
		}
	};

	using f32radian = Radian<tem_f32>;
	using f64radian = Radian<tem_f64>;

	using f32degree = Degree<tem_f32>;
	using f64degree = Degree<tem_f64>;
}