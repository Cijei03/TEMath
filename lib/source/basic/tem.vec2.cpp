#include "../../headers/basic/tem.vec2.hpp"
#include <cmath>
#include <utility>

#define TEM_LOCAL_CLASS_TEMPLATE template<temType T>

namespace tem::intern
{
    TEM_LOCAL_CLASS_TEMPLATE
    constexpr vec2<T>::vec2(const T x, const T y)
    {
        this->x = std::move(x);
        this->y = std::move(y);
    }

    TEM_LOCAL_CLASS_TEMPLATE
    constexpr vec2<T>::vec2(const T v)
    {
        this->x = std::move(v);
        this->y = std::move(v);
    }

    TEM_LOCAL_CLASS_TEMPLATE
    constexpr T vec2<T>::dot(const vec2<T>& a, const vec2<T>& b)
    {
        const intern::vec2<T> cache = a * b;
        return cache.x + cache.y;
    }

    TEM_LOCAL_CLASS_TEMPLATE
    constexpr vec2<T> vec2<T>::abs() const
    {
        if constexpr (std::is_signed_v<T>)
        {
            return vec2<T>(::abs(this->x), ::abs(this->y));
        }
        else
        {
            return *this;
        }
    }

    TEM_LOCAL_CLASS_TEMPLATE
    constexpr vec2<T> vec2<T>::normalize() const
    {
        return *this / vec2<T>(this->length());
    }

    TEM_LOCAL_CLASS_TEMPLATE
    constexpr T vec2<T>::length() const
    {
        if constexpr (std::is_signed_v<T>)
        {
            return ::abs(this->x) + ::abs(this->y);
        }
        else
        {
            return this->x + this->y;
        }
    }    

    TEM_LOCAL_CLASS_TEMPLATE
    constexpr T vec2<T>::distance(const vec2<T>& a, const vec2<T>& b)
    {
        if constexpr (std::is_signed_v<T>)
        {
            return intern::vec2<T>(a - b).abs().length();
        }
        else
        {
            return intern::vec2<T>(a - b).length();
        }
    }

    TEM_LOCAL_CLASS_TEMPLATE
    template<temType U>
    constexpr vec2<T>::operator vec2<U>() const
    {
        return vec2<U>(static_cast<U>(this->x), static_cast<U>(this->y));
    }

    TEM_LOCAL_CLASS_TEMPLATE
    constexpr const T vec2<T>::operator[](const tem_ui32 Index) const
    {
        return reinterpret_cast<const T*>(this)[Index];
    }

    TEM_LOCAL_CLASS_TEMPLATE
    constexpr T& vec2<T>::operator[](const tem_ui32 Index)
    {
        return reinterpret_cast<T*>(this)[Index];
    }

    TEM_LOCAL_CLASS_TEMPLATE
    constexpr bool vec2<T>::operator<(const vec2<T>& a) const
    {
        return (this->x < a.x && this->y < a.y);
    }

    TEM_LOCAL_CLASS_TEMPLATE
    constexpr bool vec2<T>::operator<=(const vec2<T>& a) const
    {
        return (this->x <= a.x && this->y <= a.y);
    }

    TEM_LOCAL_CLASS_TEMPLATE
    constexpr bool vec2<T>::operator==(const vec2<T>& a) const
    {
        return (this->x == a.x && this->y == a.y);
    }

    TEM_LOCAL_CLASS_TEMPLATE
    constexpr bool vec2<T>::operator>=(const vec2<T>& a) const
    {
        return (this->x >= a.x && this->y >= a.y);
    }

    TEM_LOCAL_CLASS_TEMPLATE
    constexpr bool vec2<T>::operator>(const vec2<T>& a) const
    {
        return (this->x > a.x && this->y > a.y);
    }

    TEM_LOCAL_CLASS_TEMPLATE
    constexpr vec2<T> vec2<T>::operator+(const vec2<T>& a) const
    {
        return vec2<T>(this->x + a.x, this->y + a.y);
    }

    TEM_LOCAL_CLASS_TEMPLATE
    constexpr vec2<T> vec2<T>::operator+=(const vec2<T>& a) const
    {
        return *this + a;
    }

    TEM_LOCAL_CLASS_TEMPLATE
    constexpr vec2<T> vec2<T>::operator-(const vec2<T>& a) const
    {
        return vec2<T>(this->x - a.x, this->y - a.y);
    }

    TEM_LOCAL_CLASS_TEMPLATE
    constexpr vec2<T> vec2<T>::operator-=(const vec2<T>& a) const
    {
        return *this - a;
    }

    TEM_LOCAL_CLASS_TEMPLATE
    constexpr vec2<T> vec2<T>::operator*(const vec2<T>& a) const
    {
        return vec2<T>(this->x * a.x, this->y * a.y);
    }

    TEM_LOCAL_CLASS_TEMPLATE
    constexpr vec2<T> vec2<T>::operator*=(const vec2<T>& a) const
    {
        return *this * a;
    }

    TEM_LOCAL_CLASS_TEMPLATE
    constexpr vec2<T> vec2<T>::operator/(const vec2<T>& a) const
    {
        return vec2<T>(this->x / a.x, this->y / a.y);
    }

    TEM_LOCAL_CLASS_TEMPLATE
    constexpr vec2<T> vec2<T>::operator/=(const vec2<T>& a) const
    {
        return *this / a;
    }
}

namespace tem
{
    template class intern::vec2<tem_f32>;
    template class intern::vec2<tem_f64>;

    template class intern::vec2<tem_i8>;
    template class intern::vec2<tem_i16>;
    template class intern::vec2<tem_i32>;
    template class intern::vec2<tem_i64>;

    template class intern::vec2<tem_ui8>;
    template class intern::vec2<tem_ui16>;
    template class intern::vec2<tem_ui32>;
    template class intern::vec2<tem_ui64>;
}