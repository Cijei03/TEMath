#pragma once
#include "../base/basic_preprocessor.hpp"
#include "../base/tem.basic_types.hpp"
#include "../base/tem.angle_units.hpp"
#include "../base/tem.matrix_core.hpp"
#include "tem.vec3.hpp"
#include "tem.mat2.hpp"

namespace tem::intern
{
	template<temType T>
	class mat3
	{
	private:
		vec3<T> Data[3];
	public:
		constexpr mat3() = default;
		constexpr mat3(const vec3<T>& a, const vec3<T>& b, const vec3<T>& c);

		~mat3() = default;

		constexpr void makeUnit();

		constexpr void scale(const vec3<T>& value);
		constexpr void scale(const T value);

		constexpr void rotate(const ::tem::Radian<T> angle, vec3<T> PerAxisMultiplier) requires(std::is_floating_point_v<T>);
		constexpr void rotate(const ::tem::Radian<T> AngleX, const ::tem::Radian<T> AngleY, const ::tem::Radian<T> AngleZ);

		TEM_NODISCARD constexpr mat3<T> transpose();
		TEM_NODISCARD constexpr mat3<T> inverse() requires(std::is_signed_v<T>);

		TEM_NODISCARD constexpr T getDeterminant() const;

		TEM_NODISCARD constexpr mat3<T> operator*(const mat3<T>& a) const;
		TEM_NODISCARD constexpr mat3<T> operator+(const mat3<T>& a) const;
		TEM_NODISCARD constexpr mat3<T> operator-(const mat3<T>& a) const;
		TEM_NODISCARD constexpr vec3<T> operator*(const vec3<T>& a) const;

		TEM_NODISCARD constexpr vec3<T>& operator[](const uint32_t Index);
		TEM_NODISCARD constexpr const vec3<T>& operator[](const uint32_t Index) const;

		TEM_NODISCARD constexpr const T* getPtr() const;

		template<temType U>
		TEM_NODISCARD explicit constexpr operator mat2<U>() const;

		template<temType U>
		TEM_NODISCARD explicit constexpr operator mat3<U>() const;

		static constexpr mat3<T> unitMatrix();
	};

	static_assert(MatrixCoreValidation<mat3<tem_f32>>, "Matrix 3x3 validation failed.");
}

namespace tem
{
	using f32mat3 = intern::mat3<tem_f32>;
	using f64mat3 = intern::mat3<tem_f64>;

	using i8mat3 = intern::mat3<tem_i8>;
	using i16mat3 = intern::mat3<tem_i16>;
	using i32mat3 = intern::mat3<tem_i32>;
	using i64mat3 = intern::mat3<tem_i64>;

	using ui8mat3 = intern::mat3<tem_ui8>;
	using ui16mat3 = intern::mat3<tem_ui16>;
	using ui32mat3 = intern::mat3<tem_ui32>;
	using ui64mat3 = intern::mat3<tem_ui64>;
}