#include "../headers/tem.mat4.hpp"

#define TEM_LOCAL_CLASS_TEMPLATE template<temType T>
#define M_EL(Row, Column) this->Data[Row][Column] // Alias for every matrix element.

#include <cmath>
#include <utility>

namespace tem
{
	namespace intern
	{
		TEM_LOCAL_CLASS_TEMPLATE
		constexpr mat4<T>::mat4(const vec4<T>& a, const vec4<T>& b, const vec4<T>& c, const vec4<T>& d)
		{
			this->Data[0] = std::move(a);
			this->Data[1] = std::move(b);
			this->Data[2] = std::move(c);
			this->Data[3] = std::move(d);
		}

		TEM_LOCAL_CLASS_TEMPLATE
		constexpr void mat4<T>::makeUnit()
		{
			*this = mat4<T>::unitMatrix();
		}

		TEM_LOCAL_CLASS_TEMPLATE
		constexpr void mat4<T>::scale(const vec4<T>& Value)
		{
			*this = mat4<T>(vec4<T>(Value[0], 0, 0, 0),
				vec4<T>(0, Value[1], 0, 0),
				vec4<T>(0, 0, Value[2], 0),
				vec4<T>(0, 0, 0, Value[3])) * *this;
		}

		TEM_LOCAL_CLASS_TEMPLATE
		constexpr void mat4<T>::scale(const T Value)
		{
			*this = mat4<T>(vec4<T>(Value, 0, 0, 0),
				vec4<T>(0, Value, 0, 0),
				vec4<T>(0, 0, Value, 0),
				vec4<T>(0, 0, 0, Value)) * *this;
		}

		TEM_LOCAL_CLASS_TEMPLATE
		constexpr void mat4<T>::rotate(const ::tem::Radian<T> Angle, vec3<T> PerAxisMultiplier) requires(std::is_floating_point_v<T>)
		{
			// Process input parameters.
			T PreCompCos = static_cast<T>(cos(static_cast<double>(T(Angle))));
			T PreCompSin = static_cast<T>(sin(static_cast<double>(T(Angle))));
			PerAxisMultiplier = PerAxisMultiplier.normalize();
			auto& X = PerAxisMultiplier[0];
			auto& Y = PerAxisMultiplier[1];
			auto& Z = PerAxisMultiplier[2];

			// Compute.
			mat4<T> Cache(vec4<T>(1, 0, 0, 0), vec4<T>(0, 1, 0, 0), vec4<T>(0, 0, 1, 0), vec4<T>(0, 0, 0, 1));

			// First row.
			Cache.Data[0][0] = PreCompCos + (::tem::BasicMath<T>::sqr(X)) * (1.0 - PreCompCos);
			Cache.Data[0][1] = X * Y * (1.0 - PreCompCos) - Z * PreCompSin;
			Cache.Data[0][2] = X * Z * (1.0 - PreCompCos) + Y * PreCompSin;

			// Second row.
			Cache.Data[1][0] = Y * X * (1.0 - PreCompCos) + Z * PreCompSin;
			Cache.Data[1][1] = PreCompCos + ::tem::BasicMath<T>::sqr(Y) * (1.0 - PreCompCos);
			Cache.Data[1][2] = Y * Z * (1.0 - PreCompCos) - X * PreCompSin;

			// Third row.
			Cache.Data[2][0] = Z * X * (1.0 - PreCompCos) - Y * PreCompSin;
			Cache.Data[2][1] = Z * Y * (1.0 - PreCompCos) + X * PreCompSin;
			Cache.Data[2][2] = PreCompCos + ::tem::BasicMath<T>::sqr(Z) * (1.0 - PreCompCos);

			*this = Cache * *this;
		}

		TEM_LOCAL_CLASS_TEMPLATE
		constexpr void mat4<T>::rotate(const ::tem::Radian<T> AngleX, const ::tem::Radian<T> AngleY, const ::tem::Radian<T> AngleZ)
		{
			mat4<T> AxisX(vec4<T>(1, 0, 0, 0), vec4<T>(0, 1, 0, 0), vec4<T>(0, 0, 1, 0), vec4<T>(0, 0, 0, 1));
			{
				T PreCompSin = static_cast<T>(sin(static_cast<double>(T(AngleX))));
				T PreCompCos = static_cast<T>(cos(static_cast<double>(T(AngleX))));

				AxisX.Data[1][1] = PreCompCos;
				AxisX.Data[1][2] = -PreCompSin;
				AxisX.Data[2][1] = PreCompSin;
				AxisX.Data[2][2] = PreCompCos;
			}
			mat4<T> AxisY(vec4<T>(1, 0, 0, 0), vec4<T>(0, 1, 0, 0), vec4<T>(0, 0, 1, 0), vec4<T>(0, 0, 0, 1));
			{
				T PreCompSin = static_cast<T>(sin(static_cast<double>(T(AngleY))));
				T PreCompCos = static_cast<T>(cos(static_cast<double>(T(AngleY))));

				AxisY.Data[0][0] = PreCompCos;
				AxisY.Data[0][2] = PreCompSin;
				AxisY.Data[2][0] = -PreCompSin;
				AxisY.Data[2][2] = PreCompCos;
			}

			mat4<T> AxisZ(vec4<T>(1, 0, 0, 0), vec4<T>(0, 1, 0, 0), vec4<T>(0, 0, 1, 0), vec4<T>(0, 0, 0, 1));
			{
				T PreCompSin = static_cast<T>(sin(static_cast<double>(T(AngleZ))));
				T PreCompCos = static_cast<T>(cos(static_cast<double>(T(AngleZ))));

				AxisZ.Data[0][0] = PreCompCos;
				AxisZ.Data[0][1] = -PreCompSin;
				AxisZ.Data[1][0] = PreCompSin;
				AxisZ.Data[1][1] = PreCompCos;
			}

			*this = AxisZ * AxisY * AxisX * *this;
		}

		TEM_LOCAL_CLASS_TEMPLATE
		constexpr mat4<T> mat4<T>::transpose() const
		{
			return mat4<T>(
				vec4<T>(M_EL(0, 0), M_EL(1, 0), M_EL(2, 0), M_EL(3, 0)),
				vec4<T>(M_EL(0, 1), M_EL(1, 1), M_EL(2, 1), M_EL(3, 1)),
				vec4<T>(M_EL(0, 2), M_EL(1, 2), M_EL(2, 2), M_EL(3, 2)),
				vec4<T>(M_EL(0, 3), M_EL(1, 3), M_EL(2, 3), M_EL(3, 3))
			);
		}

		TEM_LOCAL_CLASS_TEMPLATE
		constexpr mat4<T> mat4<T>::inverse() const requires(std::is_signed_v<T>)
		{
			const T Determinant = this->getDeterminant();
			
			mat4<T> AlgebraicComplementMatrix(
				vec4<T>(
					M_EL(1, 1) * M_EL(2, 2) * M_EL(3, 3) + M_EL(1, 2) * M_EL(2, 3) * M_EL(3, 1) + M_EL(1, 3) * M_EL(2, 1) * M_EL(3, 2) - M_EL(1, 1) * M_EL(2, 3) * M_EL(3, 2) - M_EL(1, 2) * M_EL(2, 1) * M_EL(3, 3) - M_EL(1, 3) * M_EL(2, 2) * M_EL(3, 1),
					M_EL(0, 1) * M_EL(2, 3) * M_EL(3, 2) + M_EL(0, 2) * M_EL(2, 1) * M_EL(3, 3) + M_EL(0, 3) * M_EL(2, 2) * M_EL(3, 1) - M_EL(0, 1) * M_EL(2, 2) * M_EL(3, 3) - M_EL(0, 2) * M_EL(2, 3) * M_EL(3, 1) - M_EL(0, 3) * M_EL(2, 1) * M_EL(3, 2),
					M_EL(0, 1) * M_EL(1, 2) * M_EL(3, 3) + M_EL(0, 2) * M_EL(1, 3) * M_EL(3, 1) + M_EL(0, 3) * M_EL(1, 1) * M_EL(3, 2) - M_EL(0, 1) * M_EL(1, 3) * M_EL(3, 2) - M_EL(0, 2) * M_EL(1, 1) * M_EL(3, 3) - M_EL(0, 3) * M_EL(1, 2) * M_EL(3, 1),
					M_EL(0, 1) * M_EL(1, 3) * M_EL(2, 2) + M_EL(0, 2) * M_EL(1, 1) * M_EL(2, 3) + M_EL(0, 3) * M_EL(1, 2) * M_EL(2, 1) - M_EL(0, 1) * M_EL(1, 2) * M_EL(2, 3) - M_EL(0, 2) * M_EL(1, 3) * M_EL(2, 1) - M_EL(0, 3) * M_EL(1, 1) * M_EL(2, 2)
				),
				vec4<T>(
					M_EL(1, 0) * M_EL(2, 3) * M_EL(3, 2) + M_EL(1, 2) * M_EL(2, 0) * M_EL(3, 3) + M_EL(1, 3) * M_EL(2, 2) * M_EL(3, 0) - M_EL(1, 0) * M_EL(2, 2) * M_EL(3, 3) - M_EL(1, 2) * M_EL(2, 3) * M_EL(3, 0) - M_EL(1, 3) * M_EL(2, 0) * M_EL(3, 2),
					M_EL(0, 0) * M_EL(2, 2) * M_EL(3, 3) + M_EL(0, 2) * M_EL(2, 3) * M_EL(3, 0) + M_EL(0, 3) * M_EL(2, 0) * M_EL(3, 2) - M_EL(0, 0) * M_EL(2, 3) * M_EL(3, 2) - M_EL(0, 2) * M_EL(2, 0) * M_EL(3, 3) - M_EL(0, 3) * M_EL(2, 2) * M_EL(3, 0),
					M_EL(0, 0) * M_EL(1, 3) * M_EL(3, 2) + M_EL(0, 2) * M_EL(1, 0) * M_EL(3, 3) + M_EL(0, 3) * M_EL(1, 2) * M_EL(3, 0) - M_EL(0, 0) * M_EL(1, 2) * M_EL(3, 3) - M_EL(0, 2) * M_EL(1, 3) * M_EL(3, 0) - M_EL(0, 3) * M_EL(1, 0) * M_EL(3, 2),
					M_EL(0, 0) * M_EL(1, 2) * M_EL(2, 3) + M_EL(0, 2) * M_EL(1, 3) * M_EL(2, 0) + M_EL(0, 3) * M_EL(1, 0) * M_EL(2, 2) - M_EL(0, 0) * M_EL(1, 3) * M_EL(2, 2) - M_EL(0, 2) * M_EL(1, 0) * M_EL(2, 3) - M_EL(0, 3) * M_EL(1, 2) * M_EL(2, 0)
				),
				vec4<T>(
					M_EL(1, 0) * M_EL(2, 3) * M_EL(3, 2) + M_EL(1, 2) * M_EL(2, 0) * M_EL(3, 3) + M_EL(1, 3) * M_EL(2, 2) * M_EL(3, 0) - M_EL(1, 0) * M_EL(2, 2) * M_EL(3, 3) - M_EL(1, 2) * M_EL(2, 3) * M_EL(3, 0) - M_EL(1, 3) * M_EL(2, 0) * M_EL(3, 2),
					M_EL(0, 0) * M_EL(2, 3) * M_EL(3, 1) + M_EL(0, 1) * M_EL(2, 0) * M_EL(3, 3) + M_EL(0, 3) * M_EL(2, 1) * M_EL(3, 0) - M_EL(0, 0) * M_EL(2, 1) * M_EL(3, 3) - M_EL(0, 1) * M_EL(2, 3) * M_EL(3, 0) - M_EL(0, 3) * M_EL(2, 0) * M_EL(3, 1),
					M_EL(0, 0) * M_EL(1, 1) * M_EL(3, 3) + M_EL(0, 1) * M_EL(1, 3) * M_EL(3, 0) + M_EL(0 ,3) * M_EL(1, 0) * M_EL(3, 1) - M_EL(0, 0) * M_EL(1, 3) * M_EL(3, 1) - M_EL(0, 1) * M_EL(1, 0) * M_EL(3, 3) - M_EL(0, 3) * M_EL(1, 1) * M_EL(3, 0),
					M_EL(0, 0) * M_EL(1, 3) * M_EL(2, 1) + M_EL(0, 1) * M_EL(1, 0) * M_EL(2, 3) + M_EL(0, 3) * M_EL(1, 1) * M_EL(2, 0) - M_EL(0, 0) * M_EL(1, 1) * M_EL(2, 3) - M_EL(0, 1) * M_EL(1, 3) * M_EL(2, 0) - M_EL(0, 3) * M_EL(1, 0) * M_EL(2, 1)
				),
				vec4<T>(
					M_EL(1, 0) * M_EL(2, 2) * M_EL(3, 1) + M_EL(1, 1) * M_EL(2, 0) * M_EL(3, 2) + M_EL(1, 2) * M_EL(2, 1) * M_EL(3, 0) - M_EL(1, 0) * M_EL(2, 1) * M_EL(3, 2) - M_EL(1, 1) * M_EL(2, 2) * M_EL(3, 0) - M_EL(1, 2) * M_EL(2, 0) * M_EL(3, 1),
					M_EL(0, 0) * M_EL(2, 1) * M_EL(3, 2) + M_EL(0, 1) * M_EL(2, 2) * M_EL(3, 0) + M_EL(0, 2) * M_EL(2, 0) * M_EL(3, 1) - M_EL(0, 0) * M_EL(2, 2) * M_EL(3, 1) - M_EL(0, 1) * M_EL(2, 0) * M_EL(3, 2) - M_EL(0, 2) * M_EL(2, 1) * M_EL(3, 0),
					M_EL(0, 0) * M_EL(1, 2) * M_EL(3, 1) + M_EL(0, 1) * M_EL(1, 0) * M_EL(3, 2) + M_EL(0, 2) * M_EL(1, 1) * M_EL(3, 0) - M_EL(0, 0) * M_EL(1, 1) * M_EL(3, 2) - M_EL(0, 1) * M_EL(1, 2) * M_EL(3, 0) - M_EL(0, 2) * M_EL(1, 0) * M_EL(3, 1),
					M_EL(0, 0) * M_EL(1, 1) * M_EL(2, 2) + M_EL(0, 1) * M_EL(1, 2) * M_EL(2, 0) + M_EL(0, 2) * M_EL(1, 0) * M_EL(2, 1) - M_EL(0, 0) * M_EL(1, 2) * M_EL(2, 1) - M_EL(0, 1) * M_EL(1, 0) * M_EL(2, 2) - M_EL(0, 2) * M_EL(1, 1) * M_EL(2, 0)
				)
			);

			if constexpr (std::is_integral_v<T>)
			{
				AlgebraicComplementMatrix[0][0] /= Determinant;
				AlgebraicComplementMatrix[0][1] /= Determinant;
				AlgebraicComplementMatrix[0][2] /= Determinant;
				AlgebraicComplementMatrix[0][3] /= Determinant;

				AlgebraicComplementMatrix[1][0] /= Determinant;
				AlgebraicComplementMatrix[1][1] /= Determinant;
				AlgebraicComplementMatrix[1][2] /= Determinant;
				AlgebraicComplementMatrix[1][3] /= Determinant;

				AlgebraicComplementMatrix[2][0] /= Determinant;
				AlgebraicComplementMatrix[2][1] /= Determinant;
				AlgebraicComplementMatrix[2][2] /= Determinant;
				AlgebraicComplementMatrix[2][3] /= Determinant;

				AlgebraicComplementMatrix[3][0] /= Determinant;
				AlgebraicComplementMatrix[3][1] /= Determinant;
				AlgebraicComplementMatrix[3][2] /= Determinant;
				AlgebraicComplementMatrix[3][3] /= Determinant;
			}
			else
			{
				const T DeterminantMul = 1.0 / Determinant;

				AlgebraicComplementMatrix[0][0] *= DeterminantMul;
				AlgebraicComplementMatrix[0][1] *= DeterminantMul;
				AlgebraicComplementMatrix[0][2] *= DeterminantMul;
				AlgebraicComplementMatrix[0][3] *= DeterminantMul;

				AlgebraicComplementMatrix[1][0] *= DeterminantMul;
				AlgebraicComplementMatrix[1][1] *= DeterminantMul;
				AlgebraicComplementMatrix[1][2] *= DeterminantMul;
				AlgebraicComplementMatrix[1][3] *= DeterminantMul;

				AlgebraicComplementMatrix[2][0] *= DeterminantMul;
				AlgebraicComplementMatrix[2][1] *= DeterminantMul;
				AlgebraicComplementMatrix[2][2] *= DeterminantMul;
				AlgebraicComplementMatrix[2][3] *= DeterminantMul;

				AlgebraicComplementMatrix[3][0] *= DeterminantMul;
				AlgebraicComplementMatrix[3][1] *= DeterminantMul;
				AlgebraicComplementMatrix[3][2] *= DeterminantMul;
				AlgebraicComplementMatrix[3][3] *= DeterminantMul;
			}

			return AlgebraicComplementMatrix;
		}

		TEM_LOCAL_CLASS_TEMPLATE
		constexpr T mat4<T>::getDeterminant() const
		{
			return 
				M_EL(0, 0) * M_EL(1, 1) * M_EL(2, 2) * M_EL(3, 3) +	M_EL(0, 0) * M_EL(1, 2) * M_EL(2, 3) * M_EL(3, 1) +	M_EL(0, 0) * M_EL(1, 3) * M_EL(2, 1) * M_EL(3, 2) +
				M_EL(0, 1) * M_EL(1, 0) * M_EL(2, 3) * M_EL(3, 2) +	M_EL(0, 1) * M_EL(1, 2) * M_EL(2, 0) * M_EL(3, 3) +	M_EL(0, 1) * M_EL(1, 3) * M_EL(2, 2) * M_EL(3, 0) +
				M_EL(0, 2) * M_EL(1, 0) * M_EL(2, 1) * M_EL(3, 3) +	M_EL(0, 2) * M_EL(1, 1) * M_EL(2, 3) * M_EL(3, 0) +	M_EL(0, 2) * M_EL(1, 3) * M_EL(2, 0) * M_EL(3, 1) +
				M_EL(0, 3) * M_EL(1, 0) * M_EL(2, 2) * M_EL(3, 1) +	M_EL(0, 3) * M_EL(1, 1) * M_EL(2, 0) * M_EL(3, 2) +	M_EL(0, 3) * M_EL(1, 2) * M_EL(2, 1) * M_EL(3, 0) -
				M_EL(0, 0) * M_EL(1, 1) * M_EL(2, 3) * M_EL(3, 2) -	M_EL(0, 0) * M_EL(1, 2) * M_EL(2, 1) * M_EL(3, 3) -	M_EL(0, 0) * M_EL(1, 3) * M_EL(2, 2) * M_EL(3, 1) -
				M_EL(0, 1) * M_EL(1, 0) * M_EL(2, 2) * M_EL(3, 3) -	M_EL(0, 1) * M_EL(1, 2) * M_EL(2, 3) * M_EL(3, 0) -	M_EL(0, 1) * M_EL(1, 3) * M_EL(2, 0) * M_EL(3, 2) -
				M_EL(0, 2) * M_EL(1, 0) * M_EL(2, 3) * M_EL(3, 1) -	M_EL(0, 2) * M_EL(1, 1) * M_EL(2, 0) * M_EL(3, 3) -	M_EL(0, 2) * M_EL(1, 3) * M_EL(2, 1) * M_EL(3, 0) -
				M_EL(0, 3) * M_EL(1, 0) * M_EL(2, 1) * M_EL(3, 2) -	M_EL(0, 3) * M_EL(1, 1) * M_EL(2, 2) * M_EL(3, 0) -	M_EL(0, 3) * M_EL(1, 2) * M_EL(2, 0) * M_EL(3, 1);
		}

		TEM_LOCAL_CLASS_TEMPLATE
		constexpr mat4<T> mat4<T>::operator*(const mat4<T>& a) const
		{
			return mat4<T>
				(
					vec4<T>
					(
						this->Data[0][0] * a.Data[0][0] + this->Data[0][1] * a.Data[1][0] + this->Data[0][2] * a.Data[2][0] + this->Data[0][3] * a.Data[3][0],
						this->Data[0][0] * a.Data[0][1] + this->Data[0][1] * a.Data[1][1] + this->Data[0][2] * a.Data[2][1] + this->Data[0][3] * a.Data[3][1],
						this->Data[0][0] * a.Data[0][2] + this->Data[0][1] * a.Data[1][2] + this->Data[0][2] * a.Data[2][2] + this->Data[0][3] * a.Data[3][2],
						this->Data[0][0] * a.Data[0][3] + this->Data[0][1] * a.Data[1][3] + this->Data[0][2] * a.Data[2][3] + this->Data[0][3] * a.Data[3][3]
					),
					vec4<T>
					(
						this->Data[1][0] * a.Data[0][0] + this->Data[1][1] * a.Data[1][0] + this->Data[1][2] * a.Data[2][0] + this->Data[1][3] * a.Data[3][0],
						this->Data[1][0] * a.Data[0][1] + this->Data[1][1] * a.Data[1][1] + this->Data[1][2] * a.Data[2][1] + this->Data[1][3] * a.Data[3][1],
						this->Data[1][0] * a.Data[0][2] + this->Data[1][1] * a.Data[1][2] + this->Data[1][2] * a.Data[2][2] + this->Data[1][3] * a.Data[3][2],
						this->Data[1][0] * a.Data[0][3] + this->Data[1][1] * a.Data[1][3] + this->Data[1][2] * a.Data[2][3] + this->Data[1][3] * a.Data[3][3]
					),
					vec4<T>
					(
						this->Data[2][0] * a.Data[0][0] + this->Data[2][1] * a.Data[1][0] + this->Data[2][2] * a.Data[2][0] + this->Data[2][3] * a.Data[3][0],
						this->Data[2][0] * a.Data[0][1] + this->Data[2][1] * a.Data[1][1] + this->Data[2][2] * a.Data[2][1] + this->Data[2][3] * a.Data[3][1],
						this->Data[2][0] * a.Data[0][2] + this->Data[2][1] * a.Data[1][2] + this->Data[2][2] * a.Data[2][2] + this->Data[2][3] * a.Data[3][2],
						this->Data[2][0] * a.Data[0][3] + this->Data[2][1] * a.Data[1][3] + this->Data[2][2] * a.Data[2][3] + this->Data[2][3] * a.Data[3][3]
					),
					vec4<T>
					(
						this->Data[3][0] * a.Data[0][0] + this->Data[3][1] * a.Data[1][0] + this->Data[3][2] * a.Data[2][0] + this->Data[3][3] * a.Data[3][0],
						this->Data[3][0] * a.Data[0][1] + this->Data[3][1] * a.Data[1][1] + this->Data[3][2] * a.Data[2][1] + this->Data[3][3] * a.Data[3][1],
						this->Data[3][0] * a.Data[0][2] + this->Data[3][1] * a.Data[1][2] + this->Data[3][2] * a.Data[2][2] + this->Data[3][3] * a.Data[3][2],
						this->Data[3][0] * a.Data[0][3] + this->Data[3][1] * a.Data[1][3] + this->Data[3][2] * a.Data[2][3] + this->Data[3][3] * a.Data[3][3]
					)
				);
		}

		TEM_LOCAL_CLASS_TEMPLATE
		constexpr mat4<T> mat4<T>::operator+(const mat4<T>& a) const
		{
			return mat4<T>
				(
					vec4<T>
					(
						this->Data[0] + a.Data[0]
					),
					vec4<T>
					(
						this->Data[1] + a.Data[1]
					),
					vec4<T>
					(
						this->Data[2] + a.Data[2]
					),
					vec4<T>
					(
						this->Data[3] + a.Data[3]
					)
				);
		}

		TEM_LOCAL_CLASS_TEMPLATE
		constexpr mat4<T> mat4<T>::operator-(const mat4<T>& a) const
		{
			return mat4<T>
				(
					vec4<T>
					(
						this->Data[0] - a.Data[0]
					),
					vec4<T>
					(
						this->Data[1] - a.Data[1]
					),
					vec4<T>
					(
						this->Data[2] - a.Data[2]
					),
					vec4<T>
					(
						this->Data[3] - a.Data[3]
					)
				);
		}

		TEM_LOCAL_CLASS_TEMPLATE
		constexpr vec4<T> mat4<T>::operator*(const vec4<T>& a) const
		{
			return vec4<T>
				(
					this->Data[0][0] * a[0] + this->Data[0][1] * a[1] + this->Data[0][2] * a[2] + this->Data[0][3] * a[3],
					this->Data[1][0] * a[0] + this->Data[1][1] * a[1] + this->Data[1][2] * a[2] + this->Data[1][3] * a[3],
					this->Data[2][0] * a[0] + this->Data[2][1] * a[1] + this->Data[2][2] * a[2] + this->Data[2][3] * a[3],
					this->Data[3][0] * a[0] + this->Data[3][1] * a[1] + this->Data[3][2] * a[2] + this->Data[3][3] * a[3]
				);
		}

		TEM_LOCAL_CLASS_TEMPLATE
		constexpr vec4<T>& mat4<T>::operator[](const uint32_t Index)
		{
			return this->Data[Index];
		}

		TEM_LOCAL_CLASS_TEMPLATE
		constexpr const vec4<T>& mat4<T>::operator[](const uint32_t Index) const
		{
			return this->Data[Index];
		}

		TEM_LOCAL_CLASS_TEMPLATE
		constexpr const T* mat4<T>::getPtr() const
		{
			return reinterpret_cast<const T*>(this);
		}

		TEM_LOCAL_CLASS_TEMPLATE
		template<temType U>
		constexpr mat4<T>::operator mat4<U>() const
		{
			return mat4<U>(
				static_cast<vec4<U>>(this->Data[0]),
				static_cast<vec4<U>>(this->Data[1]),
				static_cast<vec4<U>>(this->Data[2]),
				static_cast<vec4<U>>(this->Data[3])
			);
		}

		TEM_LOCAL_CLASS_TEMPLATE
		template<temType U>
		constexpr mat4<T>::operator mat2<U>() const
		{
			return mat2<U>(
				static_cast<vec2<U>>(this->Data[0]),
				static_cast<vec2<U>>(this->Data[1])
			);
		}

		TEM_LOCAL_CLASS_TEMPLATE
		template<temType U>
		constexpr mat4<T>::operator mat3<U>() const
		{
			return mat3<U>(
				static_cast<vec3<U>>(this->Data[0]),
				static_cast<vec3<U>>(this->Data[1]),
				static_cast<vec3<U>>(this->Data[2])
			);
		}

		TEM_LOCAL_CLASS_TEMPLATE
		constexpr mat4<T> mat4<T>::unitMatrix()
		{
			return mat4<T>(
				vec4<T>(1, 0, 0, 0), 
				vec4<T>(0, 1, 0, 0), 
				vec4<T>(0, 0, 1, 0), 
				vec4<T>(0, 0, 0, 1)
			);
		}

		TEM_LOCAL_CLASS_TEMPLATE
		mat4<T> mat4<T>::translate(const vec3<T>& value) const
		{
			return mat4<T>(vec4<T>(1, 0, 0, value.x), vec4<T>(0, 1, 0, value.y), vec4<T>(0, 0, 1, value.z), vec4<T>(0, 0, 0, 1)) * *this;
		}

		TEM_LOCAL_CLASS_TEMPLATE
		void mat4<T>::makePerspective(const ::tem::Radian<T> FOV, const vec2<T>& ScreenDimensions, const T zNear, const T zFar) requires(std::is_floating_point_v<T>)
		{
			const T aspectRatio = ScreenDimensions.x / ScreenDimensions.y;
			const T tangens = tan(static_cast<T>(FOV) * 0.5);
			const T zRange = zNear - zFar;

			this->Data[0] = vec4<T>(1.0 / (aspectRatio * tangens), 0, 0, 0);
			this->Data[1] = vec4<T>(0, 1.0 / tangens, 0, 0);
			this->Data[2] = vec4<T>(0, 0, (-zNear - zFar) / zRange, (2.0 * zNear * zFar) / zRange);
			this->Data[3] = vec4<T>(0, 0, 1.0, 0);
		}

		TEM_LOCAL_CLASS_TEMPLATE
		void mat4<T>::makeOrthogonal(const vec2<T>& FrustumDimensions, const T zNear, const T zFar) requires(std::is_floating_point_v<T>)
		{
			const T zRange = zFar - zNear;

			this->Data[0] = vec4<T>(1.0 / FrustumDimensions.x, 0, 0, 0);
			this->Data[1] = vec4<T>(0, 1.0 / FrustumDimensions.y, 0, 0);
			this->Data[2] = vec4<T>(0, 0, -(2.0 / zRange), (zFar + zNear) / zRange);
			this->Data[3] = vec4<T>(0, 0, 0, 1.0);
		}

		TEM_LOCAL_CLASS_TEMPLATE
		void mat4<T>::makeOrthogonal(const T LeftEdge, const T RightEdge, const T BottomEdge, const T TopEdge, const T zNear, const T zFar) requires(std::is_floating_point_v<T>)
		{
			const T zRange = zFar - zNear;

			this->Data[0] = vec4<T>(1.0 / (RightEdge - LeftEdge), 0, 0, 0);
			this->Data[1] = vec4<T>(0, 1.0 / (TopEdge - BottomEdge), 0, 0);
			this->Data[2] = vec4<T>(0, 0, -(2.0 / zRange), (zFar + zNear) / zRange);
			this->Data[3] = vec4<T>(0, 0, 0, 1.0);
		}

		TEM_LOCAL_CLASS_TEMPLATE
		void mat4<T>::makeLookAt(const vec3<T>& Eye, const vec3<T>& Target, const vec3<T>& Up) requires(std::is_floating_point_v<T>)
		{
			const vec3<T> CameraForward = vec3<T>(Eye - Target).normalize();
			const vec3<T> CameraRight = vec3<T>::cross(Up, CameraForward).normalize();
			const vec3<T> CameraUp = vec3<T>::cross(CameraForward, CameraRight).normalize();

			this->Data[0] = vec4<T>(CameraRight, 0);
			this->Data[1] = vec4<T>(CameraUp, 0);
			this->Data[2] = vec4<T>(CameraForward, 0);
			this->Data[3] = vec4<T>(vec3<T>(0.0), 1.0);

			*this = this->translate(vec3<T>(-Eye.x, -Eye.y, -Eye.z));
		}
	}

	template class intern::mat4<tem_f32>;
	template class intern::mat4<tem_f64>;

	template class intern::mat4<tem_i8>;
	template class intern::mat4<tem_i16>;
	template class intern::mat4<tem_i32>;
	template class intern::mat4<tem_i64>;

	template class intern::mat4<tem_ui8>;
	template class intern::mat4<tem_ui16>;
	template class intern::mat4<tem_ui32>;
	template class intern::mat4<tem_ui64>;
}