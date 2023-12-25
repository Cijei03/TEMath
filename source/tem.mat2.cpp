#include "../include/basic/tem.mat2.hpp"

#define TEM_LOCAL_CLASS_TEMPLATE template<temType T>
#define M_EL(Row, Column) this->Data[Row][Column]

#include <cmath>
#include <utility>

namespace tem::intern
{
    TEM_LOCAL_CLASS_TEMPLATE
    constexpr mat2<T>::mat2(const vec2<T>& a, const vec2<T>& b)
    {
        this->Data[0] = std::move(a);
        this->Data[1] = std::move(b);
    }    

    TEM_LOCAL_CLASS_TEMPLATE
    constexpr void mat2<T>::makeUnit()
    {
        *this = mat2<T>::unitMatrix();
    }

    TEM_LOCAL_CLASS_TEMPLATE
    constexpr void mat2<T>::scale(const vec2<T>& value)
    {
        *this = mat2<T>(vec2<T>(value[0], 0), vec2<T>(0, value[1])) * *this;
    }

    TEM_LOCAL_CLASS_TEMPLATE
    constexpr void mat2<T>::scale(const T value)
    {
        *this = mat2<T>(vec2<T>(value, 0), vec2<T>(0, value)) * *this;
    }

    TEM_LOCAL_CLASS_TEMPLATE
    constexpr void mat2<T>::rotate(const ::tem::Radian<T> angle) requires(std::is_floating_point_v<T>)
    {
        const T LocalAngle = T(angle);
        const T PrecompSin = static_cast<const T>(sin(static_cast<double>(LocalAngle)));
        const T PrecompCos = static_cast<const T>(cos(static_cast<double>(LocalAngle)));
        *this = mat2<T>(vec2<T>(PrecompCos, -PrecompSin), vec2<T>(PrecompSin, PrecompCos)) * *this;
    }

    TEM_LOCAL_CLASS_TEMPLATE
    constexpr mat2<T> mat2<T>::transpose()
    {
	    return mat2<T>(vec2<T>(M_EL(0, 0), M_EL(1, 0)), vec2<T>(M_EL(0, 1), M_EL(1, 1)));
    }

    TEM_LOCAL_CLASS_TEMPLATE
    constexpr mat2<T> mat2<T>::inverse() requires(std::is_signed_v<T>)
    {
        const T Determinant = this->getDeterminant();

        mat2<T> AlgebraicComplementMatrix = mat2<T>(
            vec2<T>(M_EL(1, 1), -M_EL(0, 1)),
            vec2<T>(-M_EL(1, 0), M_EL(0, 0))
        );

        if constexpr (std::is_integral_v<T>)
        {
            AlgebraicComplementMatrix[0][0] /= Determinant;
            AlgebraicComplementMatrix[0][1] /= Determinant;
            AlgebraicComplementMatrix[1][0] /= Determinant;
            AlgebraicComplementMatrix[1][1] /= Determinant;
        }
        else
        {
            const T DeterminantMul = 1.0 / Determinant;

            AlgebraicComplementMatrix[0][0] *= DeterminantMul;
            AlgebraicComplementMatrix[0][1] *= DeterminantMul;
            AlgebraicComplementMatrix[1][0] *= DeterminantMul;
            AlgebraicComplementMatrix[1][1] *= DeterminantMul;
        }

        return AlgebraicComplementMatrix;
    }

    TEM_LOCAL_CLASS_TEMPLATE
    constexpr T mat2<T>::getDeterminant() const
    {
        return M_EL(0, 0) * M_EL(1, 1) - M_EL(1, 0) * M_EL(0, 1);
    }

    TEM_LOCAL_CLASS_TEMPLATE
    constexpr mat2<T> mat2<T>::operator*(const mat2<T>& a)
    {
        return mat2<T>
            (
                vec2<T>
                (
                    M_EL(0, 0) * a.Data[0][0] + M_EL(0, 1) * a.Data[1][0],
                    M_EL(0, 0) * a.Data[0][1] + M_EL(0, 1) * a.Data[1][1]
                ),
                vec2<T>
                (
                    M_EL(1, 0) * a.Data[0][0] + M_EL(1, 1) * a.Data[1][0],
                    M_EL(1, 0) * a.Data[0][1] + M_EL(1, 1) * a.Data[1][1]
                )
            );
    }

    TEM_LOCAL_CLASS_TEMPLATE
    constexpr mat2<T> mat2<T>::operator+(const mat2<T>& a)
    {
        return mat2<T>
            (
                vec2<T>
                (
                    this->Data[0] + a.Data[0]
                ),
                vec2<T>
                (
                    this->Data[1] + a.Data[1]
                )
            );
    }

    TEM_LOCAL_CLASS_TEMPLATE
    constexpr mat2<T> mat2<T>::operator-(const mat2<T>& a)
    {
        return mat2<T>
            (
                vec2<T>
                (
                    this->Data[0] - a.Data[0]
                ),
                vec2<T>
                (
                    this->Data[1] - a.Data[1]
                )
            );
    }

    TEM_LOCAL_CLASS_TEMPLATE
    constexpr vec2<T> mat2<T>::operator*(const vec2<T>& a)
    {
        return vec2<T>
            (
                M_EL(0, 0) * a[0] + M_EL(0, 1) * a[1],
                M_EL(1, 0) * a[0] + M_EL(1, 1) * a[1]
            );
    }


    TEM_LOCAL_CLASS_TEMPLATE
    constexpr vec2<T>& mat2<T>::operator[](const uint32_t Index)
    {
        return this->Data[Index];
    }

    TEM_LOCAL_CLASS_TEMPLATE
    constexpr const vec2<T>& mat2<T>::operator[](const uint32_t Index) const
    {
        return this->Data[Index];
    }

    TEM_LOCAL_CLASS_TEMPLATE
    constexpr const T* mat2<T>::getPtr() const
    {
        return reinterpret_cast<const T*>(this);
    }


    TEM_LOCAL_CLASS_TEMPLATE
    template<temType U>
    constexpr mat2<T>::operator mat2<U>() const
    {
        return mat2<U>(static_cast<vec2<U>>(this->Data[0]), static_cast<vec2<U>>(this->Data[1]));
    }


    TEM_LOCAL_CLASS_TEMPLATE
    constexpr mat2<T> mat2<T>::unitMatrix()
    {
        return mat2<T> { vec2<T>(static_cast<T>(1), static_cast<T>(0)), vec2<T>(static_cast<T>(0), static_cast<T>(1)) };
    }
}

namespace tem
{
    template class intern::mat2<tem_f32>;
    template class intern::mat2<tem_f64>;

    template class intern::mat2<tem_i8>;
    template class intern::mat2<tem_i16>;
    template class intern::mat2<tem_i32>;
    template class intern::mat2<tem_i64>;

    template class intern::mat2<tem_ui8>;
    template class intern::mat2<tem_ui16>;
    template class intern::mat2<tem_ui32>;
    template class intern::mat2<tem_ui64>;
}