#pragma once
#include "../base/basic_preprocessor.hpp"
#include "../base/tem.basic_types.hpp"
#include "../base/tem.angle_units.hpp"
#include "../base/tem.matrix_core.hpp"
#include "tem.vec2.hpp"

namespace tem::intern
{
    template<temType T>
    class mat2
    {
    private:
        vec2<T> Data[2];
    public:
        constexpr mat2() = default;
        constexpr mat2(const vec2<T>& a, const vec2<T>& b);

        ~mat2() = default;

        constexpr void makeUnit();

        constexpr void scale(const vec2<T>& value);
        constexpr void scale(const T value);

        constexpr void rotate(const ::tem::Radian<T> angle) requires(std::is_floating_point_v<T>);
        TEM_NODISCARD constexpr mat2<T> transpose();
        TEM_NODISCARD constexpr mat2<T> inverse() requires(std::is_signed_v<T>);

        TEM_NODISCARD constexpr T getDeterminant() const;

        TEM_NODISCARD constexpr mat2<T> operator*(const mat2<T>& a);
        TEM_NODISCARD constexpr mat2<T> operator+(const mat2<T>& a);
        TEM_NODISCARD constexpr mat2<T> operator-(const mat2<T>& a);
        TEM_NODISCARD constexpr vec2<T> operator*(const vec2<T>& a);

        TEM_NODISCARD constexpr vec2<T>& operator[](const uint32_t Index);
        TEM_NODISCARD constexpr const vec2<T>& operator[](const uint32_t Index) const;

        TEM_NODISCARD constexpr const T* getPtr() const;

        template<temType U>
        TEM_NODISCARD explicit constexpr operator mat2<U>() const;

        static constexpr mat2<T> unitMatrix();
    };

    static_assert(MatrixCoreValidation<mat2<tem_f32>>, "Matrix validation failed.");
}

namespace tem
{
    using f32mat2 = intern::mat2<tem_f32>;
    using f64mat2 = intern::mat2<tem_f64>;

    using i8mat2 = intern::mat2<tem_i8>;
    using i16mat2 = intern::mat2<tem_i16>;
    using i32mat2 = intern::mat2<tem_i32>;
    using i64mat2 = intern::mat2<tem_i64>;

    using ui8mat2 = intern::mat2<tem_ui8>;
    using ui16mat2 = intern::mat2<tem_ui16>;
    using ui32mat2 = intern::mat2<tem_ui32>;
    using ui64mat2 = intern::mat2<tem_ui64>;
}