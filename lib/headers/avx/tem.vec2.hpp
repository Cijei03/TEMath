#pragma once
#include "../base/basic_preprocessor.hpp"
#include "../base/tem.basic_types.hpp"
#include "../base/tem.vector_core.hpp"

#include "avx_processor.hpp"

namespace tem::avx::intern
{
    template<::tem::intern::temType T>
    class vec2
    {
    public:
        T x;
        T y;
    public:
        TEM_AVX_SIMD constexpr vec2(const T x, const T y);
        TEM_AVX_SIMD constexpr vec2(const T v);

        TEM_AVX_SIMD constexpr vec2() = default;
        TEM_AVX_SIMD ~vec2() = default;

        TEM_AVX_SIMD TEM_NODISCARD constexpr const T operator[](const tem_ui32 Index) const;
        TEM_AVX_SIMD TEM_NODISCARD constexpr T& operator[](const tem_ui32 Index);

        TEM_AVX_SIMD TEM_NODISCARD constexpr bool operator<(const vec2<T>& a) const;
        TEM_AVX_SIMD TEM_NODISCARD constexpr bool operator<=(const vec2<T>& a) const;
        TEM_AVX_SIMD TEM_NODISCARD constexpr bool operator==(const vec2<T>& a) const;
        TEM_AVX_SIMD TEM_NODISCARD constexpr bool operator>=(const vec2<T>& a) const;
        TEM_AVX_SIMD TEM_NODISCARD constexpr bool operator>(const vec2<T>& a) const;

        TEM_AVX_SIMD TEM_NODISCARD constexpr vec2<T> operator+(const vec2<T>& a) const;
        TEM_AVX_SIMD TEM_NODISCARD constexpr vec2<T> operator+=(const vec2<T>& a) const;

        TEM_AVX_SIMD TEM_NODISCARD constexpr vec2<T> operator-(const vec2<T>& a) const;
        TEM_AVX_SIMD TEM_NODISCARD constexpr vec2<T> operator-=(const vec2<T>& a) const;

        TEM_AVX_SIMD TEM_NODISCARD constexpr vec2<T> operator*(const vec2<T>& a) const;
        TEM_AVX_SIMD TEM_NODISCARD constexpr vec2<T> operator*=(const vec2<T>& a) const;

        TEM_AVX_SIMD TEM_NODISCARD constexpr vec2<T> operator/(const vec2<T>& a) const;
        TEM_AVX_SIMD TEM_NODISCARD constexpr vec2<T> operator/=(const vec2<T>& a) const;

        template<::tem::intern::temType U>
        TEM_AVX_SIMD TEM_NODISCARD explicit constexpr operator vec2<U>() const;

        TEM_AVX_SIMD TEM_NODISCARD constexpr vec2<T> abs() const;
        TEM_AVX_SIMD TEM_NODISCARD constexpr vec2<T> normalize() const;
        TEM_AVX_SIMD TEM_NODISCARD constexpr T length() const;

        TEM_AVX_SIMD static constexpr T dot(const vec2<T>& a, const vec2<T>& b);
        TEM_AVX_SIMD static constexpr T distance(const vec2<T>& a, const vec2<T>& b);
    };

    static_assert(::tem::intern::VectorCoreValidation<vec2<tem_ui32>>, "Vector validation failed");
}
namespace tem::avx
{
    using f32vec2 = intern::vec2<tem_f32>;
    using f64vec2 = intern::vec2<tem_f64>;

    using i8vec2 = intern::vec2<tem_i8>;
    using i16vec2 = intern::vec2<tem_i16>;
    using i32vec2 = intern::vec2<tem_i32>;
    using i64vec2 = intern::vec2<tem_i64>;

    using ui8vec2 = intern::vec2<tem_ui8>;
    using ui16vec2 = intern::vec2<tem_ui16>;
    using ui32vec2 = intern::vec2<tem_ui32>;
    using ui64vec2 = intern::vec2<tem_ui64>;
}