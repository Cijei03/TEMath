#pragma once
#include "basic_preprocessor.hpp"

#include "tem.basic_types.hpp"
#include "tem.vector_core.hpp"

namespace tem
{
	namespace intern
	{
        template<temType T>
        class vec2
        {
        public:
            T x;
            T y;
        public:
            constexpr vec2(const T x, const T y);
            constexpr vec2(const T v);

            constexpr vec2() = default;
            ~vec2() = default;

            TEM_NODISCARD constexpr const T operator[](const tem_ui32 Index) const;
            TEM_NODISCARD constexpr T& operator[](const tem_ui32 Index);

            TEM_NODISCARD constexpr bool operator<(const vec2<T>& a) const;
            TEM_NODISCARD constexpr bool operator<=(const vec2<T>& a) const;
            TEM_NODISCARD constexpr bool operator==(const vec2<T>& a) const;
            TEM_NODISCARD constexpr bool operator>=(const vec2<T>& a) const;
            TEM_NODISCARD constexpr bool operator>(const vec2<T>& a) const;

            TEM_NODISCARD constexpr vec2<T> operator+(const vec2<T>& a) const;
            TEM_NODISCARD constexpr vec2<T> operator+=(const vec2<T>& a) const;

            TEM_NODISCARD constexpr vec2<T> operator-(const vec2<T>& a) const;
            TEM_NODISCARD constexpr vec2<T> operator-=(const vec2<T>& a) const;

            TEM_NODISCARD constexpr vec2<T> operator*(const vec2<T>& a) const;
            TEM_NODISCARD constexpr vec2<T> operator*=(const vec2<T>& a) const;

            TEM_NODISCARD constexpr vec2<T> operator/(const vec2<T>& a) const;
            TEM_NODISCARD constexpr vec2<T> operator/=(const vec2<T>& a) const;

            template<temType U>
            TEM_NODISCARD explicit constexpr operator vec2<U>() const;

            TEM_NODISCARD constexpr vec2<T> abs() const;
            TEM_NODISCARD constexpr vec2<T> normalize() const;
            TEM_NODISCARD constexpr T length() const;

            static constexpr T dot(const vec2<T>& a, const vec2<T>& b);
            static constexpr T distance(const vec2<T>& a, const vec2<T>& b);
        };

        static_assert(VectorCoreValidation<vec2<tem_ui32>>, "Vector validation failed");
    }
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