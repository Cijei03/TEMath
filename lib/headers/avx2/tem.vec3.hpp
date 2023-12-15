#pragma once
#include "../base/basic_preprocessor.hpp"
#include "../base/tem.basic_types.hpp"
#include "../base/tem.vector_core.hpp"
#include "tem.vec2.hpp"

#include "avx2_processor.hpp"

namespace tem::avx2::intern
{
    template<::tem::intern::temType T>
    class vec3
    {
    public:
        T x;
        T y;
        T z;
    public:
        TEM_AVX2_FMA3_SIMD constexpr vec3(const T x, const T y, const T z);
        TEM_AVX2_FMA3_SIMD constexpr vec3(const T v);

        TEM_AVX2_FMA3_SIMD constexpr vec3(const vec2<T>& v, const T z);
        TEM_AVX2_FMA3_SIMD constexpr vec3(const T x, const vec2<T>& v);

        TEM_AVX2_FMA3_SIMD constexpr vec3() = default;
        TEM_AVX2_FMA3_SIMD ~vec3() = default;

        TEM_AVX2_FMA3_SIMD TEM_NODISCARD constexpr T& operator[](const uint32_t Index);
        TEM_AVX2_FMA3_SIMD TEM_NODISCARD constexpr const T& operator[](const uint32_t Index) const;

        TEM_AVX2_FMA3_SIMD TEM_NODISCARD constexpr bool operator<(const vec3<T>& a) const;
        TEM_AVX2_FMA3_SIMD TEM_NODISCARD constexpr bool operator<=(const vec3<T>& a) const;
        TEM_AVX2_FMA3_SIMD TEM_NODISCARD constexpr bool operator==(const vec3<T>& a) const;
        TEM_AVX2_FMA3_SIMD TEM_NODISCARD constexpr bool operator>=(const vec3<T>& a) const;
        TEM_AVX2_FMA3_SIMD TEM_NODISCARD constexpr bool operator>(const vec3<T>& a) const;

        TEM_AVX2_FMA3_SIMD TEM_NODISCARD constexpr vec3<T> operator+(const vec3<T>& a) const;
        TEM_AVX2_FMA3_SIMD TEM_NODISCARD constexpr vec3<T> operator+=(const vec3<T>& a) const;

        TEM_AVX2_FMA3_SIMD TEM_NODISCARD constexpr vec3<T> operator-(const vec3<T>& a) const;
        TEM_AVX2_FMA3_SIMD TEM_NODISCARD constexpr vec3<T> operator-=(const vec3<T>& a) const;

        TEM_AVX2_FMA3_SIMD TEM_NODISCARD constexpr vec3<T> operator*(const vec3<T>& a) const;
        TEM_AVX2_FMA3_SIMD TEM_NODISCARD constexpr vec3<T> operator*=(const vec3<T>& a) const;

        TEM_AVX2_FMA3_SIMD TEM_NODISCARD constexpr vec3<T> operator/(const vec3<T>& a) const;
        TEM_AVX2_FMA3_SIMD TEM_NODISCARD constexpr vec3<T> operator/=(const vec3<T>& a) const;

        template<::tem::intern::temType U>
        TEM_AVX2_FMA3_SIMD TEM_NODISCARD explicit constexpr operator vec3<U>() const;
        template<::tem::intern::temType U>
        TEM_AVX2_FMA3_SIMD TEM_NODISCARD explicit constexpr operator vec2<U>() const;

        TEM_AVX2_FMA3_SIMD TEM_NODISCARD constexpr vec3<T> abs() const;
        TEM_AVX2_FMA3_SIMD TEM_NODISCARD constexpr vec3<T> normalize() const;
        TEM_AVX2_FMA3_SIMD TEM_NODISCARD constexpr T length() const;

        TEM_AVX2_FMA3_SIMD static constexpr T dot(const vec3<T>& a, const vec3<T>& b);
        TEM_AVX2_FMA3_SIMD static constexpr T distance(const vec3<T>& a, const vec3<T>& b);
        TEM_AVX2_FMA3_SIMD static constexpr vec3<T> cross(const vec3<T>& a, const vec3<T>& b);
    };

    static_assert(::tem::intern::VectorCoreValidation<vec3<tem_ui32>>, "Vector validation failed");
}

namespace tem::avx2
{
    using f32vec3 = intern::vec3<tem_f32>;
    using f64vec3 = intern::vec3<tem_f64>;

    using i8vec3 = intern::vec3<tem_i8>;
    using i16vec3 = intern::vec3<tem_i16>;
    using i32vec3 = intern::vec3<tem_i32>;
    using i64vec3 = intern::vec3<tem_i64>;

    using ui8vec3 = intern::vec3<tem_ui8>;
    using ui16vec3 = intern::vec3<tem_ui16>;
    using ui32vec3 = intern::vec3<tem_ui32>;
    using ui64vec3 = intern::vec3<tem_ui64>;
}