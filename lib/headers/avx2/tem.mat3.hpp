#pragma once
#include "../base/basic_preprocessor.hpp"
#include "../base/tem.basic_types.hpp"
#include "../base/tem.angle_units.hpp"
#include "../base/tem.matrix_core.hpp"
#include "tem.vec3.hpp"
#include "tem.mat2.hpp"

#include "avx2_processor.hpp"

namespace tem::avx2::intern
{
	template<::tem::intern::temType T>
	class mat3
	{
	private:
		vec3<T> Data[3];
	public:
		TEM_AVX2_FMA3_SIMD constexpr mat3() = default;
		TEM_AVX2_FMA3_SIMD constexpr mat3(const vec3<T>& a, const vec3<T>& b, const vec3<T>& c);

		TEM_AVX2_FMA3_SIMD ~mat3() = default;

		TEM_AVX2_FMA3_SIMD constexpr void makeUnit();

		TEM_AVX2_FMA3_SIMD constexpr void scale(const vec3<T>& value);
		TEM_AVX2_FMA3_SIMD constexpr void scale(const T value);

		TEM_AVX2_FMA3_SIMD constexpr void rotate(const ::tem::Radian<T> angle, vec3<T> PerAxisMultiplier) requires(std::is_floating_point_v<T>);
		TEM_AVX2_FMA3_SIMD constexpr void rotate(const ::tem::Radian<T> AngleX, const ::tem::Radian<T> AngleY, const ::tem::Radian<T> AngleZ);

		TEM_AVX2_FMA3_SIMD TEM_NODISCARD constexpr mat3<T> transpose();
		TEM_AVX2_FMA3_SIMD TEM_NODISCARD constexpr mat3<T> inverse() requires(std::is_signed_v<T>);

		TEM_AVX2_FMA3_SIMD TEM_NODISCARD constexpr T getDeterminant() const;

		TEM_AVX2_FMA3_SIMD TEM_NODISCARD constexpr mat3<T> operator*(const mat3<T>& a) const;
		TEM_AVX2_FMA3_SIMD TEM_NODISCARD constexpr mat3<T> operator+(const mat3<T>& a) const;
		TEM_AVX2_FMA3_SIMD TEM_NODISCARD constexpr mat3<T> operator-(const mat3<T>& a) const;
		TEM_AVX2_FMA3_SIMD TEM_NODISCARD constexpr vec3<T> operator*(const vec3<T>& a) const;

		TEM_AVX2_FMA3_SIMD TEM_NODISCARD constexpr vec3<T>& operator[](const uint32_t Index);
		TEM_AVX2_FMA3_SIMD TEM_NODISCARD constexpr const vec3<T>& operator[](const uint32_t Index) const;

		TEM_AVX2_FMA3_SIMD TEM_NODISCARD constexpr const T* getPtr() const;

		template<::tem::intern::temType U>
		TEM_AVX2_FMA3_SIMD TEM_NODISCARD explicit constexpr operator mat2<U>() const;

		template<::tem::intern::temType U>
		TEM_AVX2_FMA3_SIMD TEM_NODISCARD explicit constexpr operator mat3<U>() const;

		TEM_AVX2_FMA3_SIMD static constexpr mat3<T> unitMatrix();
	};

	static_assert(::tem::intern::MatrixCoreValidation<mat3<tem_f32>>, "Matrix 3x3 validation failed.");
}

namespace tem::avx2
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