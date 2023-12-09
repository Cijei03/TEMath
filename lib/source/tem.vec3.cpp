#include <cmath>
#include <utility>
#include "../headers/tem.vec3.hpp"

#define TEM_LOCAL_CLASS_TEMPLATE template<temType T>

namespace tem::intern
{
    TEM_LOCAL_CLASS_TEMPLATE
    constexpr vec3<T>::vec3(const T x, const T y, const T z)
    {
        this->x = std::move(x);
        this->y = std::move(y);
        this->z = std::move(z);
    }

    TEM_LOCAL_CLASS_TEMPLATE
    constexpr vec3<T>::vec3(const T v)
    {
        this->x = std::move(v);
        this->y = std::move(v);
        this->z = std::move(v);
    }

    TEM_LOCAL_CLASS_TEMPLATE
    constexpr vec3<T>::vec3(const vec2<T>& v, const T z)
    {
        this->x = std::move(v.x);
        this->y = std::move(v.y);
        this->z = std::move(z);
    }

    TEM_LOCAL_CLASS_TEMPLATE
    constexpr vec3<T>::vec3(const T x, const vec2<T>& v)
    {
        this->x = std::move(x);
        this->y = std::move(v.x);
        this->z = std::move(v.y);
    }

    TEM_LOCAL_CLASS_TEMPLATE
    constexpr T& vec3<T>::operator[](const uint32_t Index)
    {
        return reinterpret_cast<T*>(this)[Index];
    }

    TEM_LOCAL_CLASS_TEMPLATE
    constexpr const T& vec3<T>::operator[](const uint32_t Index) const
    {
        return reinterpret_cast<const T*>(this)[Index];
    }

    TEM_LOCAL_CLASS_TEMPLATE
    constexpr bool vec3<T>::operator<(const vec3<T>& a) const
    {
        return (this->x < a.x && this->y < a.y && this->z < a.z);
    }

    TEM_LOCAL_CLASS_TEMPLATE
    constexpr bool vec3<T>::operator<=(const vec3<T>& a) const
    {
        return (this->x <= a.x && this->y <= a.y && this->z <= a.z);
    }

    TEM_LOCAL_CLASS_TEMPLATE
    constexpr bool vec3<T>::operator==(const vec3<T>& a) const
    {
        return (this->x == a.x && this->y == a.y && this->z == a.z);
    }

    TEM_LOCAL_CLASS_TEMPLATE
    constexpr bool vec3<T>::operator>=(const vec3<T>& a) const
    {
        return (this->x >= a.x && this->y >= a.y && this->z >= a.z);
    }

    TEM_LOCAL_CLASS_TEMPLATE
    constexpr bool vec3<T>::operator>(const vec3<T>& a) const
    {
        return (this->x > a.x && this->y > a.y && this->z > a.z);
    }

    TEM_LOCAL_CLASS_TEMPLATE
    constexpr vec3<T> vec3<T>::operator+(const vec3<T>& a) const
    {
        return vec3<T>(this->x + a.x, this->y + a.y, this->z + a.z);
    }

    TEM_LOCAL_CLASS_TEMPLATE
    constexpr vec3<T> vec3<T>::operator+=(const vec3<T>& a) const
    {
        return *this + a;
    }

    TEM_LOCAL_CLASS_TEMPLATE
    constexpr vec3<T> vec3<T>::operator-(const vec3<T>& a) const
    {
        return vec3<T>(this->x - a.x, this->y - a.y, this->z - a.z);
    }

    TEM_LOCAL_CLASS_TEMPLATE
    constexpr vec3<T> vec3<T>::operator-=(const vec3<T>& a) const
    {
        return *this - a;
    }

    TEM_LOCAL_CLASS_TEMPLATE
    constexpr vec3<T> vec3<T>::operator*(const vec3<T>& a) const
    {
        return vec3<T>(this->x * a.x, this->y * a.y, this->z * a.z);
    }

    TEM_LOCAL_CLASS_TEMPLATE
    constexpr vec3<T> vec3<T>::operator*=(const vec3<T>& a) const
    {
        return *this * a;
    }

    TEM_LOCAL_CLASS_TEMPLATE
    constexpr vec3<T> vec3<T>::operator/(const vec3<T>& a) const
    {
        return vec3<T>(this->x / a.x, this->y / a.y, this->z / a.z);
    }

    TEM_LOCAL_CLASS_TEMPLATE
    constexpr vec3<T> vec3<T>::operator/=(const vec3<T>& a) const
    {
        return *this / a;
    }

    TEM_LOCAL_CLASS_TEMPLATE
    constexpr vec3<T> vec3<T>::abs() const
    {
        if constexpr (std::is_signed_v<T>)
        {
            return vec3<T>(::abs(this->x), ::abs(this->y), ::abs(this->z));
        }
        else
        {
            return *this;
        }
    }

    TEM_LOCAL_CLASS_TEMPLATE
    constexpr T vec3<T>::length() const
    {
        if constexpr (std::is_signed_v<T>)
        {
            return ::abs(this->x) + ::abs(this->y) + ::abs(this->z);
        }
        else
        {
            return this->x + this->y + this->z;
        }
    }

    TEM_LOCAL_CLASS_TEMPLATE
    constexpr vec3<T> vec3<T>::normalize() const
    {
        return *this / vec3<T>(this->length());
    }

    TEM_LOCAL_CLASS_TEMPLATE
    constexpr T vec3<T>::dot(const vec3<T>& a, const vec3<T>& b)
    {
        const intern::vec3<T> cache = a * b;
        return cache.x + cache.y + cache.z;
    }

    TEM_LOCAL_CLASS_TEMPLATE
    constexpr T vec3<T>::distance(const vec3<T>& a, const vec3<T>& b)
    {
        return intern::vec3<T>(a - b).abs().length();
    }

    TEM_LOCAL_CLASS_TEMPLATE
    constexpr vec3<T> vec3<T>::cross(const vec3<T>& a, const vec3<T>& b)
    {
        return intern::vec3<T>
            (
                (a.y * b.z) - (a.z * b.y),
                (a.z * b.x) - (a.x * b.z),
                (a.x * b.y) - (a.y * b.x)
            );
    }

    TEM_LOCAL_CLASS_TEMPLATE
    template<temType U>
    constexpr vec3<T>::operator vec3<U>() const
    {
        return vec3<U>(static_cast<U>(this->x), static_cast<U>(this->y), static_cast<U>(this->z));
    }

    TEM_LOCAL_CLASS_TEMPLATE
    template<temType U>
    constexpr vec3<T>::operator vec2<U>() const
    {
        return vec2<U>(static_cast<U>(this->x), static_cast<U>(this->y));
    }
}

namespace tem
{
    template class intern::vec3<tem_f32>;
    template class intern::vec3<tem_f64>;

    template class intern::vec3<tem_i8>;
    template class intern::vec3<tem_i16>;
    template class intern::vec3<tem_i32>;
    template class intern::vec3<tem_i64>;

    template class intern::vec3<tem_ui8>;
    template class intern::vec3<tem_ui16>;
    template class intern::vec3<tem_ui32>;
    template class intern::vec3<tem_ui64>;
}