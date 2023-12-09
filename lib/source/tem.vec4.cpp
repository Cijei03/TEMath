#include <cmath>
#include <utility>
#include "../headers/tem.vec4.hpp"

#define TEM_LOCAL_CLASS_TEMPLATE template<temType T>

namespace tem::intern
{
    TEM_LOCAL_CLASS_TEMPLATE
    constexpr vec4<T>::vec4(const T x, const T y, const T z, const T w)
    {
        this->x = std::move(x);
        this->y = std::move(y);
        this->z = std::move(z);
        this->w = std::move(w);
    }

    TEM_LOCAL_CLASS_TEMPLATE
    constexpr vec4<T>::vec4(const T v)
    {
        this->x = std::move(v);
        this->y = std::move(v);
        this->z = std::move(v);
        this->w = std::move(v);
    }
    
    TEM_LOCAL_CLASS_TEMPLATE
    constexpr vec4<T>::vec4(const vec2<T>& xy, const T z, const T w)
    {
        this->x = std::move(xy.x);
        this->y = std::move(xy.y);
        this->z = std::move(z);
        this->w = std::move(w);
    }

    TEM_LOCAL_CLASS_TEMPLATE
    constexpr vec4<T>::vec4(const T x, const vec2<T>& yz, const T w)
    {
        this->x = x;
        this->y = yz.x;
        this->z = yz.y;
        this->w = w;
    }

    TEM_LOCAL_CLASS_TEMPLATE
    constexpr vec4<T>::vec4(const T x, const T y, const vec2<T>& zw)
    {
        this->x = x;
        this->y = y;
        this->z = zw.x;
        this->w = zw.y;
    }

    TEM_LOCAL_CLASS_TEMPLATE
    constexpr vec4<T>::vec4(const vec2<T>& xy, const vec2<T> zw)
    {
        this->x = xy.x;
        this->y = xy.y;
        this->z = zw.x;
        this->w = zw.y;
    }

    TEM_LOCAL_CLASS_TEMPLATE
    constexpr vec4<T>::vec4(const vec3<T>& xyz, const T w)
    {
        this->x = xyz.x;
        this->y = xyz.y;
        this->z = xyz.z;
        this->w = w;
    }

    TEM_LOCAL_CLASS_TEMPLATE
    constexpr vec4<T>::vec4(const T x, const vec3<T>& yzw)
    {
        this->x = x;
        this->y = yzw.x;
        this->z = yzw.y;
        this->w = yzw.z;
    }

    TEM_LOCAL_CLASS_TEMPLATE
    constexpr T& vec4<T>::operator[](const uint32_t Index)
    {
        return reinterpret_cast<T*>(this)[Index];
    }

    TEM_LOCAL_CLASS_TEMPLATE
    constexpr const T& vec4<T>::operator[](const uint32_t Index) const
    {
        return reinterpret_cast<const T*>(this)[Index];
    }

    TEM_LOCAL_CLASS_TEMPLATE
    constexpr bool vec4<T>::operator<(const vec4<T>& a) const
    {
        return (this->x < a.x && this->y < a.y && this->z < a.z && this->w < a.w);
    }

    TEM_LOCAL_CLASS_TEMPLATE
    constexpr bool vec4<T>::operator<=(const vec4<T>& a) const
    {
        return (this->x <= a.x && this->y <= a.y && this->z <= a.z && this->w <= a.w);
    }

    TEM_LOCAL_CLASS_TEMPLATE
    constexpr bool vec4<T>::operator==(const vec4<T>& a) const
    {
        return (this->x == a.x && this->y == a.y && this->z == a.z && this->w == a.w);
    }

    TEM_LOCAL_CLASS_TEMPLATE
    constexpr bool vec4<T>::operator>=(const vec4<T>& a) const
    {
        return (this->x >= a.x && this->y >= a.y && this->z >= a.z && this->w >= a.w);
    }

    TEM_LOCAL_CLASS_TEMPLATE
    constexpr bool vec4<T>::operator>(const vec4<T>& a) const
    {
        return (this->x > a.x && this->y > a.y && this->z > a.z && this->w > a.w);
    }

    TEM_LOCAL_CLASS_TEMPLATE
    constexpr vec4<T> vec4<T>::operator+(const vec4<T>& a) const
    {
        return vec4<T>(this->x + a.x, this->y + a.y, this->z + a.z, this->w + a.w);
    }

    TEM_LOCAL_CLASS_TEMPLATE
    constexpr vec4<T> vec4<T>::operator+=(const vec4<T>& a) const
    {
        return *this + a;
    }

    TEM_LOCAL_CLASS_TEMPLATE
    constexpr vec4<T> vec4<T>::operator-(const vec4<T>& a) const
    {
        return vec4<T>(this->x - a.x, this->y - a.y, this->z - a.z, this->w - a.w);
    }

    TEM_LOCAL_CLASS_TEMPLATE
    constexpr vec4<T> vec4<T>::operator-=(const vec4<T>& a) const
    {
        return *this - a;
    }

    TEM_LOCAL_CLASS_TEMPLATE
    constexpr vec4<T> vec4<T>::operator*(const vec4<T>& a) const
    {
        return vec4<T>(this->x * a.x, this->y * a.y, this->z * a.z, this->w * a.w);
    }

    TEM_LOCAL_CLASS_TEMPLATE
    constexpr vec4<T> vec4<T>::operator*=(const vec4<T>& a) const
    {
        return *this * a;
    }

    TEM_LOCAL_CLASS_TEMPLATE
    constexpr vec4<T> vec4<T>::operator/(const vec4<T>& a) const
    {
        return vec4<T>(this->x / a.x, this->y / a.y, this->z / a.z, this->w / a.w);
    }

    TEM_LOCAL_CLASS_TEMPLATE
    constexpr vec4<T> vec4<T>::operator/=(const vec4<T>& a) const
    {
        return *this / a;
    }

    TEM_LOCAL_CLASS_TEMPLATE
    template<temType U>
    constexpr vec4<T>::operator vec4<U>() const
    {
        return vec4<U>(static_cast<U>(this->x), static_cast<U>(this->y), static_cast<U>(this->z), static_cast<U>(this->w));
    }

    TEM_LOCAL_CLASS_TEMPLATE
    template<temType U>
    constexpr vec4<T>::operator vec3<U>() const
    {
        return vec3<U>(static_cast<U>(this->x), static_cast<U>(this->y), static_cast<U>(this->z));
    }

    TEM_LOCAL_CLASS_TEMPLATE
    template<temType U>
    constexpr vec4<T>::operator vec2<U>() const
    {
        return vec2<U>(static_cast<U>(this->x), static_cast<U>(this->y));
    }

    TEM_LOCAL_CLASS_TEMPLATE
    constexpr vec4<T> vec4<T>::abs() const
    {
        if constexpr (std::is_signed_v<T>)
        {
            return vec4<T>(::abs(this->x), ::abs(this->y), ::abs(this->z), ::abs(this->w));
        }
        else
        {
            return *this;
        }
    }

    TEM_LOCAL_CLASS_TEMPLATE
    constexpr vec4<T> vec4<T>::normalize() const
    {
        return *this / vec4<T>(this->length());
    }

    TEM_LOCAL_CLASS_TEMPLATE
    constexpr T vec4<T>::length() const
    {
        if constexpr (std::is_signed_v<T>)
        {
            return ::abs(this->x) + ::abs(this->y) + ::abs(this->z) + ::abs(this->w);
        }
        else
        {
            return this->x + this->y + this->z + this->w;
        }
    }

    TEM_LOCAL_CLASS_TEMPLATE
    constexpr T vec4<T>::dot(const vec4<T>& a, const vec4<T>& b)
    {
        const intern::vec4<T> cache = a * b;
        return cache.x + cache.y + cache.z + cache.w;
    }

    TEM_LOCAL_CLASS_TEMPLATE
    constexpr T vec4<T>::distance(const vec4<T>& a, const vec4<T>& b)
    {
        return intern::vec4<T>(a - b).abs().length();
    }
}

namespace tem
{
    template class intern::vec4<tem_f32>;
    template class intern::vec4<tem_f64>;

    template class intern::vec4<tem_i8>;
    template class intern::vec4<tem_i16>;
    template class intern::vec4<tem_i32>;
    template class intern::vec4<tem_i64>;

    template class intern::vec4<tem_ui8>;
    template class intern::vec4<tem_ui16>;
    template class intern::vec4<tem_ui32>;
    template class intern::vec4<tem_ui64>;
}