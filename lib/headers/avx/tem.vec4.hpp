#pragma once
#include "../base/basic_preprocessor.hpp"
#include "../base/tem.basic_types.hpp"
#include "../base/tem.vector_core.hpp"
#include "tem.vec2.hpp"
#include "tem.vec3.hpp"

#include "avx_processor.hpp"

namespace tem::avx::intern
{
    template<::tem::intern::temType T>
    class vec4
    {
    public:
        T x;
        T y;
        T z;
        T w;
    public:
        TEM_AVX_SIMD constexpr vec4(const T x, const T y, const T z, const T w);
        TEM_AVX_SIMD constexpr vec4(const T v);
        /* BY MULTI COMPONENTS CONSTRUCTORS */
        TEM_AVX_SIMD constexpr vec4(const vec2<T>& xy, const T z, const T w);
        TEM_AVX_SIMD constexpr vec4(const T x, const vec2<T>& yz, const T w);
        TEM_AVX_SIMD constexpr vec4(const T x, const T y, const vec2<T>& zw);
        TEM_AVX_SIMD constexpr vec4(const vec2<T>& xy, const vec2<T> zw);

        TEM_AVX_SIMD constexpr vec4(const vec3<T>& xyz, const T w);
        TEM_AVX_SIMD constexpr vec4(const T x, const vec3<T>& yzw);

        TEM_AVX_SIMD constexpr vec4() = default;
        TEM_AVX_SIMD ~vec4() = default;

        TEM_AVX_SIMD TEM_NODISCARD constexpr T& operator[](const uint32_t Index);
        TEM_AVX_SIMD TEM_NODISCARD constexpr const T& operator[](const uint32_t Index) const;

        TEM_AVX_SIMD TEM_NODISCARD constexpr bool operator<(const vec4<T>& a) const;
        TEM_AVX_SIMD TEM_NODISCARD constexpr bool operator<=(const vec4<T>& a) const;
        TEM_AVX_SIMD TEM_NODISCARD constexpr bool operator==(const vec4<T>& a) const;
        TEM_AVX_SIMD TEM_NODISCARD constexpr bool operator>=(const vec4<T>& a) const;
        TEM_AVX_SIMD TEM_NODISCARD constexpr bool operator>(const vec4<T>& a) const;

        TEM_AVX_SIMD TEM_NODISCARD constexpr vec4<T> operator+(const vec4<T>& a) const;
        TEM_AVX_SIMD TEM_NODISCARD constexpr vec4<T> operator+=(const vec4<T>& a) const;

        TEM_AVX_SIMD TEM_NODISCARD constexpr vec4<T> operator-(const vec4<T>& a) const;
        TEM_AVX_SIMD TEM_NODISCARD constexpr vec4<T> operator-=(const vec4<T>& a) const;

        TEM_AVX_SIMD TEM_NODISCARD constexpr vec4<T> operator*(const vec4<T>& a) const;
        TEM_AVX_SIMD TEM_NODISCARD constexpr vec4<T> operator*=(const vec4<T>& a) const;

        TEM_AVX_SIMD TEM_NODISCARD constexpr vec4<T> operator/(const vec4<T>& a) const;
        TEM_AVX_SIMD TEM_NODISCARD constexpr vec4<T> operator/=(const vec4<T>& a) const;

        template<::tem::intern::temType U>
        TEM_AVX_SIMD TEM_NODISCARD explicit constexpr operator vec4<U>() const;
        template<::tem::intern::temType U>
        TEM_AVX_SIMD TEM_NODISCARD explicit constexpr operator vec3<U>() const;
        template<::tem::intern::temType U>
        TEM_AVX_SIMD TEM_NODISCARD explicit constexpr operator vec2<U>() const;

        TEM_AVX_SIMD TEM_NODISCARD constexpr vec4<T> abs() const;
        TEM_AVX_SIMD TEM_NODISCARD constexpr vec4<T> normalize() const;
        TEM_AVX_SIMD TEM_NODISCARD constexpr T length() const;

        TEM_AVX_SIMD TEM_NODISCARD static constexpr T dot(const vec4<T>& a, const vec4<T>& b);
        TEM_AVX_SIMD TEM_NODISCARD static constexpr T distance(const vec4<T>& a, const vec4<T>& b);
    };

    static_assert(::tem::intern::VectorCoreValidation<vec4<tem_ui32>>, "Vector validation failed");
}

namespace tem::avx
{
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