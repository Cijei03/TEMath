#pragma once
#include "basic_preprocessor.hpp"
#include "tem.basic_types.hpp"
#include "tem.vector_core.hpp"
#include "tem.vec2.hpp"
#include "tem.vec3.hpp"

namespace tem
{
	namespace intern
	{
        template<temType T>
        class vec4
        {
        public:
            T x;
            T y;
            T z;
            T w;
        public:
            /* BY SINGLE COMPONENTS CONSTRUCTORS */
            constexpr vec4(const T x, const T y, const T z, const T w);
            constexpr vec4(const T v);
            /* BY MULTI COMPONENTS CONSTRUCTORS */
            constexpr vec4(const vec2<T>& xy, const T z, const T w);
            constexpr vec4(const T x, const vec2<T>& yz, const T w);
            constexpr vec4(const T x, const T y, const vec2<T>& zw);
            constexpr vec4(const vec2<T>& xy, const vec2<T> zw);

            constexpr vec4(const vec3<T>& xyz, const T w);
            constexpr vec4(const T x, const vec3<T>& yzw);

            constexpr vec4() = default;
            ~vec4() = default;

            TEM_NODISCARD constexpr T& operator[](const uint32_t Index);
            TEM_NODISCARD constexpr const T& operator[](const uint32_t Index) const;

            TEM_NODISCARD constexpr bool operator<(const vec4<T>& a) const;
            TEM_NODISCARD constexpr bool operator<=(const vec4<T>& a) const;
            TEM_NODISCARD constexpr bool operator==(const vec4<T>& a) const;
            TEM_NODISCARD constexpr bool operator>=(const vec4<T>& a) const;
            TEM_NODISCARD constexpr bool operator>(const vec4<T>& a) const;

            TEM_NODISCARD constexpr vec4<T> operator+(const vec4<T>& a) const;
            TEM_NODISCARD constexpr vec4<T> operator+=(const vec4<T>& a) const;

            TEM_NODISCARD constexpr vec4<T> operator-(const vec4<T>& a) const;
            TEM_NODISCARD constexpr vec4<T> operator-=(const vec4<T>& a) const;

            TEM_NODISCARD constexpr vec4<T> operator*(const vec4<T>& a) const;
            TEM_NODISCARD constexpr vec4<T> operator*=(const vec4<T>& a) const;

            TEM_NODISCARD constexpr vec4<T> operator/(const vec4<T>& a) const;
            TEM_NODISCARD constexpr vec4<T> operator/=(const vec4<T>& a) const;

            template<temType U>
            TEM_NODISCARD explicit constexpr operator vec4<U>() const;
            template<temType U>
            TEM_NODISCARD explicit constexpr operator vec3<U>() const;
            template<temType U>
            TEM_NODISCARD explicit constexpr operator vec2<U>() const;

            TEM_NODISCARD constexpr vec4<T> abs() const;
            TEM_NODISCARD constexpr vec4<T> normalize() const;
            TEM_NODISCARD constexpr T length() const;

            TEM_NODISCARD static constexpr T dot(const vec4<T>& a, const vec4<T>& b);
            TEM_NODISCARD static constexpr T distance(const vec4<T>& a, const vec4<T>& b);
        };

        static_assert(VectorCoreValidation<vec4<tem_ui32>>, "Vector validation failed");
    }

    using f32vec4 = intern::vec4<tem_f32>;
    using f64vec4 = intern::vec4<tem_f64>;

    using i8vec4 = intern::vec4<tem_i8>;
    using i16vec4 = intern::vec4<tem_i16>;
    using i32vec4 = intern::vec4<tem_i32>;
    using i64vec4 = intern::vec4<tem_i64>;

    using ui8vec4 = intern::vec4<tem_ui8>;
    using ui16vec4 = intern::vec4<tem_ui16>;
    using ui32vec4 = intern::vec4<tem_ui32>;
    using ui64vec4 = intern::vec4<tem_ui64>;
}