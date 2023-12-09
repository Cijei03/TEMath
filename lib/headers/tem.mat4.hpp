#pragma once
#include "basic_preprocessor.hpp"
#include "tem.basic_types.hpp"
#include "tem.matrix_core.hpp"
#include "tem.vec2.hpp"
#include "tem.vec3.hpp"
#include "tem.vec4.hpp"
#include "tem.mat2.hpp"
#include "tem.mat3.hpp"

namespace tem
{
	namespace intern
	{
		template<temType T>
		class mat4
		{
		private:
			vec4<T> Data[4];

		public:
			constexpr mat4() = default;
			constexpr mat4(const vec4<T>& a, const vec4<T>& b, const vec4<T>& c, const vec4<T>& d);

			~mat4() = default;

			constexpr void makeUnit();

			constexpr void scale(const vec4<T>& Value);
			constexpr void scale(const T Value);

			constexpr void rotate(const ::tem::Radian<T> Angle, vec3<T> PerAxisMultiplier) requires(std::is_floating_point_v<T>);
			constexpr void rotate(const ::tem::Radian<T> AngleX, const ::tem::Radian<T> AngleY, const ::tem::Radian<T> AngleZ);

			TEM_NODISCARD constexpr mat4<T> transpose() const;
			TEM_NODISCARD constexpr mat4<T> inverse() const requires(std::is_signed_v<T>);

			TEM_NODISCARD constexpr T getDeterminant() const;

			TEM_NODISCARD constexpr mat4<T> operator*(const mat4<T>& a) const;
			TEM_NODISCARD constexpr mat4<T> operator+(const mat4<T>& a) const;
			TEM_NODISCARD constexpr mat4<T> operator-(const mat4<T>& a) const;
			TEM_NODISCARD constexpr vec4<T> operator*(const vec4<T>& a) const;

			TEM_NODISCARD constexpr vec4<T>& operator[](const uint32_t Index);
			TEM_NODISCARD constexpr const vec4<T>& operator[](const uint32_t Index) const;

			TEM_NODISCARD constexpr const T* getPtr() const;

			template<temType U>
			TEM_NODISCARD explicit constexpr operator mat2<U>() const;

			template<temType U>
			TEM_NODISCARD explicit constexpr operator mat3<U>() const;
			
			template<temType U>
			TEM_NODISCARD explicit constexpr operator mat4<U>() const;

			static constexpr mat4<T> unitMatrix();

			TEM_NODISCARD mat4<T> translate(const vec3<T>& value) const;

			void makePerspective(const ::tem::Radian<T> FOV, const vec2<T>& ScreenDimensions, const T zNear, const T zFar) requires(std::is_floating_point_v<T>);

			void makeOrthogonal(const vec2<T>& FrustumDimensions, const T zNear, const T zFar) requires(std::is_floating_point_v<T>);
			void makeOrthogonal(const T LeftEdge, const T RightEdge, const T BottomEdge, const T TopEdge, const T zNear, const T zFar) requires(std::is_floating_point_v<T>);

			void makeLookAt(const vec3<T>& Eye, const vec3<T>& Target, const vec3<T>& Up) requires(std::is_floating_point_v<T>);
		};

		static_assert(MatrixCoreValidation<mat4<tem_f32>>, "Matrix 4x4 validation failed.");
	}

	using f32mat4 = intern::mat4<tem_f32>;
	using f64mat4 = intern::mat4<tem_f64>;

	using i8mat4 = intern::mat4<tem_i8>;
	using i16mat4 = intern::mat4<tem_i16>;
	using i32mat4 = intern::mat4<tem_i32>;
	using i64mat4 = intern::mat4<tem_i64>;

	using ui8mat4 = intern::mat4<tem_ui8>;
	using ui16mat4 = intern::mat4<tem_ui16>;
	using ui32mat4 = intern::mat4<tem_ui32>;
	using ui64mat4 = intern::mat4<tem_ui64>;
}