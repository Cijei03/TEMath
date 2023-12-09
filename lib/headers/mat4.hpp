#pragma once
#include <algorithm>
#include <type_traits>
#include "../temBasicTypes.hpp"
#include "../vector/vec4.hpp"
#include "../temBasic.hpp"

namespace tem::intern
{
    template<typename T>
    class mat4
    {
    private:
        vec4<T> Data[4];
    public:
        constexpr mat4() = default;
        ~mat4() = default;

        /* CONSTRUCTORS */
        constexpr mat4(const vec4<T>& a, const vec4<T>& b, const vec4<T>& c, const vec4<T>& d)
        {
            this->Data[0] = a;
            this->Data[1] = b;
            this->Data[2] = c;
            this->Data[3] = d;
        }
        mat4(T* existingDataPtr)
        {
            // First row.
            this->Data[0].x = existingDataPtr[0];
            this->Data[0].y = existingDataPtr[1];
            this->Data[0].z = existingDataPtr[2];
            this->Data[0].w = existingDataPtr[3];
            // Second row.
            this->Data[1].x = existingDataPtr[4];
            this->Data[1].y = existingDataPtr[5];
            this->Data[1].z = existingDataPtr[6];
            this->Data[1].w = existingDataPtr[7];
            // Third row.
            this->Data[2].x = existingDataPtr[8];
            this->Data[2].y = existingDataPtr[9];
            this->Data[2].z = existingDataPtr[10];
            this->Data[2].w = existingDataPtr[11];
            // Forth row.
            this->Data[3].x = existingDataPtr[12];
            this->Data[3].y = existingDataPtr[13];
            this->Data[3].z = existingDataPtr[14];
            this->Data[3].w = existingDataPtr[15];
        }
        void makeUnit()
        {
            this->Data[0] = vec4<T>(1, 0, 0, 0);
            this->Data[1] = vec4<T>(0, 1, 0, 0);
            this->Data[2] = vec4<T>(0, 0, 1, 0);
            this->Data[3] = vec4<T>(0, 0, 0, 1);
        }
        void scale(const vec4<T>& value)
        {
            *this = mat4<T>(vec4<T>(value.x, 0, 0, 0), vec4<T>(0, value.y, 0, 0), vec4<T>(0, 0, value.z, 0), vec4<T>(0, 0, 0, value.w)) * *this;
        }
        void scale(const T value)
        {
            *this = mat4<T>(vec4<T>(value, 0, 0, 0), vec4<T>(0, value, 0, 0), vec4<T>(0, 0, value, 0), vec4<T>(0, 0, 0, value)) * *this;
        }
        void rotate(tem_f32 angle, vec3<tem_f32> perAxisMultiplier)
        {
            // Process input parameters.
            angle = ::tem::BasicMath<T>::DigreesToRadians(angle);
            tem_f32 preCompCos = cos(angle);
            tem_f32 preCompSin = sin(angle);
            perAxisMultiplier = perAxisMultiplier.normalize();
            auto& X = perAxisMultiplier.x;
            auto& Y = perAxisMultiplier.y;
            auto& Z = perAxisMultiplier.z;

            // Compute.
            mat4<T> cache(vec4<T>(1, 0, 0, 0), vec4<T>(0, 1, 0, 0), vec4<T>(0, 0, 1, 0), vec4<T>(0, 0, 0, 1));

            // First row.
            cache.Data[0].x = preCompCos + (::tem::BasicMath<T>::sqr(X)) * (1.0f - preCompCos);
            cache.Data[0].y = X * Y * (1.0f - preCompCos) - Z * preCompSin;
            cache.Data[0].z = X * Z * (1.0f - preCompCos) + Y * preCompSin;

            // Second row.
            cache.Data[1].x = Y * X * (1.0f - preCompCos) + Z * preCompSin;
            cache.Data[1].y = preCompCos + ::tem::BasicMath<T>::sqr(Y) * (1.0f - preCompCos);
            cache.Data[1].z = Y * Z * (1.0f - preCompCos) - X * preCompSin;

            // Third row.
            cache.Data[2].x = Z * X * (1.0f - preCompCos) - Y * preCompSin;
            cache.Data[2].y = Z * Y * (1.0f - preCompCos) + X * preCompSin;
            cache.Data[2].z = preCompCos + ::tem::BasicMath<T>::sqr(Z) * (1.0f - preCompCos);

            *this = cache * *this;
        }
        void rotate(vec3<tem_f32> angles)
        {
            mat4<T> axisX(vec4<T>(1, 0, 0, 0), vec4<T>(0, 1, 0, 0), vec4<T>(0, 0, 1, 0), vec4<T>(0, 0, 0, 1));
            {
                angles.x = ::tem::BasicMath<T>::DigreesToRadians(angles.x);
                tem_f32 preCompSin = sin(angles.x);
                tem_f32 preCompCos = cos(angles.x);

                axisX.Data[1].y = preCompCos;
                axisX.Data[1].z = -preCompSin;
                axisX.Data[2].y = preCompSin;
                axisX.Data[2].z = preCompCos;
            }
            mat4<T> axisY(vec4<T>(1, 0, 0, 0), vec4<T>(0, 1, 0, 0), vec4<T>(0, 0, 1, 0), vec4<T>(0, 0, 0, 1));
            {
                angles.y = ::tem::BasicMath<T>::DigreesToRadians(angles.y);
                tem_f32 preCompSin = sin(angles.y);
                tem_f32 preCompCos = cos(angles.y);

                axisY.Data[0].x = preCompCos;
                axisY.Data[0].z = preCompSin;
                axisY.Data[2].x = -preCompSin;
                axisY.Data[2].z = preCompCos;
            }
            mat4<T> axisZ(vec4<T>(1, 0, 0, 0), vec4<T>(0, 1, 0, 0), vec4<T>(0, 0, 1, 0), vec4<T>(0, 0, 0, 1));
            {
                angles.z = ::tem::BasicMath<T>::DigreesToRadians(angles.z);
                tem_f32 preCompSin = sin(angles.z);
                tem_f32 preCompCos = cos(angles.z);

                axisZ.Data[0].x = preCompCos;
                axisZ.Data[0].y = -preCompSin;
                axisZ.Data[1].x = preCompSin;
                axisZ.Data[1].y = preCompCos;
            }

            *this = axisZ * axisY * axisX * *this;
        }
        void translate(const vec3<T>& value)
        {
            *this = mat4<T>(vec4<T>(1, 0, 0, value.x), vec4<T>(0, 1, 0, value.y), vec4<T>(0, 0, 1, value.z), vec4<T>(0, 0, 0, 1)) * *this;
        }
        void transpose()
        {
            std::swap(this->Data[0].y, this->Data[1].x);
            std::swap(this->Data[0].z, this->Data[2].x);
            std::swap(this->Data[0].w, this->Data[3].x);
            std::swap(this->Data[1].z, this->Data[2].y);
            std::swap(this->Data[1].w, this->Data[3].y);
            std::swap(this->Data[2].w, this->Data[3].z);
            std::swap(this->Data[3].z, this->Data[2].w);
        }
        void makePerspective(const T FOV, const vec2<T>& screenDimensions, const T zNear, const T zFar) requires(std::is_floating_point_v<T>)
        {
            const T aspectRatio = screenDimensions.x / screenDimensions.y;
            const T tangens = tan(::tem::BasicMath<T>::DigreesToRadians(FOV) * 0.5f);
            const T zRange = zNear - zFar;

            this->Data[0] = vec4<T>(1.0f / (aspectRatio * tangens), 0, 0, 0);
            this->Data[1] = vec4<T>(0, 1.0f / tangens, 0, 0);
            this->Data[2] = vec4<T>(0, 0, (-zNear - zFar) / zRange, (2.0f * zNear * zFar) / zRange);
            this->Data[3] = vec4<T>(0, 0, 1.0f, 0);
        }
        void makeOrthogonal(const vec2<T>& frustumDimensions, const T zNear, const T zFar)
        {
            const T zRange = zFar - zNear;

            this->Data[0] = f32vec4(1.0f / frustumDimensions.x, 0, 0, 0);
            this->Data[1] = f32vec4(0, 1.0f / frustumDimensions.y, 0, 0);
            this->Data[2] = f32vec4(0, 0, -(2.0f / zRange), (zFar + zNear) / zRange);
            this->Data[3] = f32vec4(0, 0, 0, 1.0f);
        }
        void makeOrthogonal(const T leftEdge, const T rightEdge, const T bottomEdge, const T topEdge, const T zNear, const T zFar)
        {
            const T zRange = zFar - zNear;

            this->Data[0] = f32vec4(1.0f / (rightEdge - leftEdge), 0, 0, 0);
            this->Data[1] = f32vec4(0, 1.0f / (topEdge - bottomEdge), 0, 0);
            this->Data[2] = f32vec4(0, 0, -(2.0f / zRange), (zFar + zNear) / zRange);
            this->Data[3] = f32vec4(0, 0, 0, 1.0f);
        }
        void makeLookAt(const vec3<T>& eye, const vec3<T>& target, const vec3<T>& up)
        {
            const vec3<T> cameraForward = normalize(eye - target);
            const vec3<T> cameraRight = normalize(cross(up, cameraForward));
            const vec3<T> cameraUp = normalize(cross(cameraForward, cameraRight));

            this->Data[0] = vec4<T>(cameraRight, 0);
            this->Data[1] = vec4<T>(cameraUp, 0);
            this->Data[2] = vec4<T>(cameraForward, 0);
            this->Data[3] = vec4<T>(vec3<T>(0.0f), 1.0f);

            this->translate(vec3<T>(-eye.x, -eye.y, -eye.z));
        }
        /* ARITHMETHIC WITH OTHER MATRICES */
        TEM_NODISCARD friend mat4<T> operator*(const mat4<T>& a, const mat4<T>& b)
        {
            return mat4<T>
                (
                    vec4<T>
                    (
                        a.Data[0].x * b.Data[0].x + a.Data[0].y * b.Data[1].x + a.Data[0].z * b.Data[2].x + a.Data[0].w * b.Data[3].x,
                        a.Data[0].x * b.Data[0].y + a.Data[0].y * b.Data[1].y + a.Data[0].z * b.Data[2].y + a.Data[0].w * b.Data[3].y,
                        a.Data[0].x * b.Data[0].z + a.Data[0].y * b.Data[1].z + a.Data[0].z * b.Data[2].z + a.Data[0].w * b.Data[3].z,
                        a.Data[0].x * b.Data[0].w + a.Data[0].y * b.Data[1].w + a.Data[0].z * b.Data[2].w + a.Data[0].w * b.Data[3].w
                    ),
                    vec4<T>
                    (
                        a.Data[1].x * b.Data[0].x + a.Data[1].y * b.Data[1].x + a.Data[1].z * b.Data[2].x + a.Data[1].w * b.Data[3].x,
                        a.Data[1].x * b.Data[0].y + a.Data[1].y * b.Data[1].y + a.Data[1].z * b.Data[2].y + a.Data[1].w * b.Data[3].y,
                        a.Data[1].x * b.Data[0].z + a.Data[1].y * b.Data[1].z + a.Data[1].z * b.Data[2].z + a.Data[1].w * b.Data[3].z,
                        a.Data[1].x * b.Data[0].w + a.Data[1].y * b.Data[1].w + a.Data[1].z * b.Data[2].w + a.Data[1].w * b.Data[3].w
                    ),
                    vec4<T>
                    (
                        a.Data[2].x * b.Data[0].x + a.Data[2].y * b.Data[1].x + a.Data[2].z * b.Data[2].x + a.Data[2].w * b.Data[3].x,
                        a.Data[2].x * b.Data[0].y + a.Data[2].y * b.Data[1].y + a.Data[2].z * b.Data[2].y + a.Data[2].w * b.Data[3].y,
                        a.Data[2].x * b.Data[0].z + a.Data[2].y * b.Data[1].z + a.Data[2].z * b.Data[2].z + a.Data[2].w * b.Data[3].z,
                        a.Data[2].x * b.Data[0].w + a.Data[2].y * b.Data[1].w + a.Data[2].z * b.Data[2].w + a.Data[2].w * b.Data[3].w
                    ),
                    vec4<T>
                    (
                        a.Data[3].x * b.Data[0].x + a.Data[3].y * b.Data[1].x + a.Data[3].z * b.Data[2].x + a.Data[3].w * b.Data[3].x,
                        a.Data[3].x * b.Data[0].y + a.Data[3].y * b.Data[1].y + a.Data[3].z * b.Data[2].y + a.Data[3].w * b.Data[3].y,
                        a.Data[3].x * b.Data[0].z + a.Data[3].y * b.Data[1].z + a.Data[3].z * b.Data[2].z + a.Data[3].w * b.Data[3].z,
                        a.Data[3].x * b.Data[0].w + a.Data[3].y * b.Data[1].w + a.Data[3].z * b.Data[2].w + a.Data[3].w * b.Data[3].w
                    )
                );
        }
        TEM_NODISCARD friend mat4<T> operator+(const mat4<T>& a, const mat4<T>& b)
        {
            return mat4<T>
                (
                    vec4<T>
                    (
                        a.Data[0] + b.Data[0]
                    ),
                    vec4<T>
                    (
                        a.Data[1] + b.Data[1]
                    ),
                    vec4<T>
                    (
                        a.Data[2] + b.Data[2]
                    ),
                    vec4<T>
                    (
                        a.Data[3] + b.Data[3]
                    )
                );
        }
        TEM_NODISCARD friend mat4<T> operator-(const mat4<T>& a, const mat4<T>& b)
        {
            return mat4<T>
                (
                    vec4<T>
                    (
                        a.Data[0] - b.Data[0]
                    ),
                    vec4<T>
                    (
                        a.Data[1] - b.Data[1]
                    ),
                    vec4<T>
                    (
                        a.Data[2] - b.Data[2]
                    ),
                    vec4<T>
                    (
                        a.Data[3] - b.Data[3]
                    )
                );
        }
        /* ARITHMETHIC WITH VECTOR */
        TEM_NODISCARD friend vec4<T> operator*(const mat4<T>& a, const vec4<T>& b)
        {
            return vec4<T>
                (
                    a.Data[0].x * b.x + a.Data[0].y * b.y + a.Data[0].z * b.z + a.Data[0].w * b.w,
                    a.Data[1].x * b.x + a.Data[1].y * b.y + a.Data[1].z * b.z + a.Data[1].w * b.w,
                    a.Data[2].x * b.x + a.Data[2].y * b.y + a.Data[2].z * b.z + a.Data[2].w * b.w,
                    a.Data[3].x * b.x + a.Data[3].y * b.y + a.Data[3].z * b.z + a.Data[3].w * b.w
                );
        }
        static consteval mat4<T> unitMatrix()
        {
            return mat4<T>(vec4<T>(1, 0, 0, 0), vec4<T>(0, 1, 0, 0), vec4<T>(0, 0, 1, 0), vec4<T>(0, 0, 0, 1));
        }
        TEM_NODISCARD T* get()
        {
            return &this->Data[0].x;
        }
        TEM_NODISCARD vec4<T>& operator[](const uint32_t Index)
        {
            return this->Data[Index];
        }
    };
}
namespace tem
{
    using f32mat4 = intern::mat4<tem_f32>;
    using f64mat4 = intern::mat4<tem_f64>;

    using i8mat4 = intern::mat4<tem_i8>;
    using i16mat4 = intern::mat4<tem_i16>;
    using i32mat4 = intern::mat4<tem_i32>;
    using i64mat4 = intern::mat4<tem_i64>;

    using ui8mat4 = intern::mat4<tem_ui8>;
    using ui16mat4 = intern::mat4<tem_ui16>;
    using ui32mat4 = intern::mat4<tem_ui32>;
    using ui64mat4 = intern::mat4<tem_ui64>;
}