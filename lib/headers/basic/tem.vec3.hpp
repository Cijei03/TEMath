#pragma once
#include "../base/basic_preprocessor.hpp"
#include "../base/tem.basic_types.hpp"
#include "../base/tem.vector_core.hpp"
#include "tem.vec2.hpp"

namespace tem::intern
{
    template<temType T>
    class vec3
    {
    public:
        T x;
        T y;
        T z;
    public:
        constexpr vec3(const T x, const T y, const T z);
        constexpr vec3(const T v);

        constexpr vec3(const vec2<T>& v, const T z);
        constexpr vec3(const T x, const vec2<T>& v);

        constexpr vec3() = default;
        ~vec3() = default;

        TEM_NODISCARD constexpr T& operator[](const uint32_t Index);
        TEM_NODISCARD constexpr const T& operator[](const uint32_t Index) const;

        TEM_NODISCARD constexpr bool operator<(const vec3<T>& a) const;
        TEM_NODISCARD constexpr bool operator<=(const vec3<T>& a) const;
        TEM_NODISCARD constexpr bool operator==(const vec3<T>& a) const;
        TEM_NODISCARD constexpr bool operator>=(const vec3<T>& a) const;
        TEM_NODISCARD constexpr bool operator>(const vec3<T>& a) const;

        TEM_NODISCARD constexpr vec3<T> operator+(const vec3<T>& a) const;
        TEM_NODISCARD constexpr vec3<T> operator+=(const vec3<T>& a) const;

        TEM_NODISCARD constexpr vec3<T> operator-(const vec3<T>& a) const;
        TEM_NODISCARD constexpr vec3<T> operator-=(const vec3<T>& a) const;

        TEM_NODISCARD constexpr vec3<T> operator*(const vec3<T>& a) const;
        TEM_NODISCARD constexpr vec3<T> operator*=(const vec3<T>& a) const;

        TEM_NODISCARD constexpr vec3<T> operator/(const vec3<T>& a) const;
        TEM_NODISCARD constexpr vec3<T> operator/=(const vec3<T>& a) const;

        template<temType U>
        TEM_NODISCARD explicit constexpr operator vec3<U>() const;
        template<temType U>
        TEM_NODISCARD explicit constexpr operator vec2<U>() const;

        TEM_NODISCARD constexpr vec3<T> abs() const;
        TEM_NODISCARD constexpr vec3<T> normalize() const;
        TEM_NODISCARD constexpr T length() const;

        static constexpr T dot(const vec3<T>& a, const vec3<T>& b);
        static constexpr T distance(const vec3<T>& a, const vec3<T>& b);
        static constexpr vec3<T> cross(const vec3<T>& a, const vec3<T>& b);
    };

    static_assert(VectorCoreValidation<vec3<tem_ui32>>, "Vector validation failed");
}

namespace tem
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