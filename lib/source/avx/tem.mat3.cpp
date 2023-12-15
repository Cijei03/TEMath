#include "../../headers/avx/tem.mat3.hpp"
#include <cmath>
#include <utility>

#define TEM_LOCAL_CLASS_TEMPLATE template<::tem::intern::temType T>
#define M_EL(Row, Column) this->Data[Row][Column]	// Alias for every matrix element.

namespace tem::avx::intern
{
	TEM_LOCAL_CLASS_TEMPLATE
	constexpr mat3<T>::mat3(const vec3<T>& a, const vec3<T>& b, const vec3<T>& c)
	{
		this->Data[0] = std::move(a);
		this->Data[1] = std::move(b);
		this->Data[2] = std::move(c);
	}

	TEM_LOCAL_CLASS_TEMPLATE
	constexpr void mat3<T>::makeUnit()
	{
		*this = mat3<T>::unitMatrix();
	}

	TEM_LOCAL_CLASS_TEMPLATE
	constexpr void mat3<T>::scale(const vec3<T>& Value)
	{
		*this = mat3<T>(vec3<T>(Value[0], 0, 0), vec3<T>(0, Value[1], 0), vec3<T>(0, 0, Value[2])) * *this;
	}

	TEM_LOCAL_CLASS_TEMPLATE
	constexpr void mat3<T>::scale(const T Value)
	{
		*this = mat3<T>(vec3<T>(Value, 0, 0), vec3<T>(0, Value, 0), vec3<T>(0, 0, Value)) * *this;
	}

	TEM_LOCAL_CLASS_TEMPLATE
	constexpr void mat3<T>::rotate(const ::tem::Radian<T> Angle, vec3<T> PerAxisMultiplier) requires(std::is_floating_point_v<T>)
	{
		// Process input parameters.
		T PreCompCos = static_cast<T>(cos(static_cast<double>(T(Angle))));
		T PreCompSin = static_cast<T>(sin(static_cast<double>(T(Angle))));
		PerAxisMultiplier = PerAxisMultiplier.normalize();
		auto& X = PerAxisMultiplier[0];
		auto& Y = PerAxisMultiplier[1];
		auto& Z = PerAxisMultiplier[2];

		// Compute.
		mat3<T> Cache(vec3<T>(1, 0, 0), vec3<T>(0, 1, 0), vec3<T>(0, 0, 1));
		
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
	constexpr void mat3<T>::rotate(const ::tem::Radian<T> AngleX, const ::tem::Radian<T> AngleY, const ::tem::Radian<T> AngleZ)
	{
		mat3<T> AxisX(vec3<T>(1, 0, 0), vec3<T>(0, 1, 0), vec3<T>(0, 0, 1));
		{
			T PreCompSin = static_cast<T>(sin(static_cast<double>(T(AngleX))));
			T PreCompCos = static_cast<T>(cos(static_cast<double>(T(AngleX))));

			AxisX.Data[1][1] = PreCompCos;
			AxisX.Data[1][2] = -PreCompSin;
			AxisX.Data[2][1] = PreCompSin;
			AxisX.Data[2][2] = PreCompCos;
		}
		mat3<T> AxisY(vec3<T>(1, 0, 0), vec3<T>(0, 1, 0), vec3<T>(0, 0, 1));
		{
			T PreCompSin = static_cast<T>(sin(static_cast<double>(T(AngleY))));
			T PreCompCos = static_cast<T>(cos(static_cast<double>(T(AngleY))));

			AxisY.Data[0][0] = PreCompCos;
			AxisY.Data[0][2] = PreCompSin;
			AxisY.Data[2][0] = -PreCompSin;
			AxisY.Data[2][2] = PreCompCos;
		}

		mat3<T> AxisZ(vec3<T>(1, 0, 0), vec3<T>(0, 1, 0), vec3<T>(0, 0, 1));
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
	constexpr mat3<T> mat3<T>::transpose()
	{
		return mat3<T>(
			vec3<T>(M_EL(0, 0), M_EL(1, 0), M_EL(2, 0)),
			vec3<T>(M_EL(0, 1), M_EL(1, 1), M_EL(2, 1)),
			vec3<T>(M_EL(0, 2), M_EL(1, 2), M_EL(2, 2))
		);
	}

	TEM_LOCAL_CLASS_TEMPLATE
	constexpr mat3<T> mat3<T>::inverse() requires(std::is_signed_v<T>)
	{
		const T Determinant = this->getDeterminant();

		mat3<T> AlgebraicComplementMatrix(
			vec3<T>(
				M_EL(1, 1) * M_EL(2, 2) - M_EL(1, 2) * M_EL(2, 1),
				M_EL(0, 2) * M_EL(2, 1) - M_EL(0, 1) * M_EL(2, 2),
				M_EL(0, 1) * M_EL(1, 2) - M_EL(0, 2) * M_EL(1, 1)
			),
			vec3<T>(
				M_EL(1, 2) * M_EL(2, 0) - M_EL(1, 0) * M_EL(2, 2),
				M_EL(0, 0) * M_EL(2, 2) - M_EL(0, 2) * M_EL(2, 0),
				M_EL(0, 2) * M_EL(1, 0) - M_EL(0, 0) * M_EL(0, 0)
			),
			vec3<T>(
				M_EL(1, 0) * M_EL(2, 1) - M_EL(1, 1) * M_EL(2, 0),
				M_EL(0, 1) * M_EL(2, 0) - M_EL(0, 0) * M_EL(2, 1),
				M_EL(0, 0) * M_EL(1, 1) - M_EL(0, 1) * M_EL(1, 0)
			)
		);

		if constexpr (std::is_integral_v<T>)
		{
			AlgebraicComplementMatrix[0][0] /= Determinant;
			AlgebraicComplementMatrix[0][1] /= Determinant;
			AlgebraicComplementMatrix[0][2] /= Determinant;
			AlgebraicComplementMatrix[1][0] /= Determinant;
			AlgebraicComplementMatrix[1][1] /= Determinant;
			AlgebraicComplementMatrix[1][2] /= Determinant;
			AlgebraicComplementMatrix[2][0] /= Determinant;
			AlgebraicComplementMatrix[2][1] /= Determinant;
			AlgebraicComplementMatrix[2][2] /= Determinant;
		}
		else
		{
			const T DeterminantMul = 1.0 / Determinant;

			AlgebraicComplementMatrix[0][0] *= DeterminantMul;
			AlgebraicComplementMatrix[0][1] *= DeterminantMul;
			AlgebraicComplementMatrix[0][2] *= DeterminantMul;
			AlgebraicComplementMatrix[1][0] *= DeterminantMul;
			AlgebraicComplementMatrix[1][1] *= DeterminantMul;
			AlgebraicComplementMatrix[1][2] *= DeterminantMul;
			AlgebraicComplementMatrix[2][0] *= DeterminantMul;
			AlgebraicComplementMatrix[2][1] *= DeterminantMul;
			AlgebraicComplementMatrix[2][2] *= DeterminantMul;
		}

		return AlgebraicComplementMatrix;
	}

	TEM_LOCAL_CLASS_TEMPLATE
	constexpr T mat3<T>::getDeterminant() const
	{
		return M_EL(0, 0) * M_EL(1, 1) * M_EL(2, 2) +
			M_EL(0, 1) * M_EL(1, 2) * M_EL(2, 0) +
			M_EL(0, 2) * M_EL(1, 0) * M_EL(2, 1) -
			M_EL(0, 2) * M_EL(1, 1) * M_EL(2, 0) -
			M_EL(0, 0) * M_EL(1, 2) * M_EL(2, 1) -
			M_EL(0, 1) * M_EL(1, 0) * M_EL(2, 2);
	}

	TEM_LOCAL_CLASS_TEMPLATE
	constexpr mat3<T> mat3<T>::operator*(const mat3<T>& a) const
	{
		return mat3<T>
			(
				vec3<T>
				(
					M_EL(0, 0) * a.Data[0][0] + M_EL(0, 1) * a.Data[1][0] + M_EL(0, 2) * a.Data[2][0],
					M_EL(0, 0) * a.Data[0][1] + M_EL(0, 1) * a.Data[1][1] + M_EL(0, 2) * a.Data[2][1],
					M_EL(0, 0) * a.Data[0][2] + M_EL(0, 1) * a.Data[1][2] + M_EL(0, 2) * a.Data[2][2]
				),
				vec3<T>
				(
					M_EL(1, 0) * a.Data[0][0] + M_EL(1, 1) * a.Data[1][0] + M_EL(1, 2) * a.Data[2][0],
					M_EL(1, 0) * a.Data[0][1] + M_EL(1, 1) * a.Data[1][1] + M_EL(1, 2) * a.Data[2][1],
					M_EL(1, 0) * a.Data[0][2] + M_EL(1, 1) * a.Data[1][2] + M_EL(1, 2) * a.Data[2][2]
				),
				vec3<T>
				(
					M_EL(2, 0) * a.Data[0][0] + M_EL(2, 1) * a.Data[1][0] + M_EL(2, 2) * a.Data[2][0],
					M_EL(2, 0) * a.Data[0][1] + M_EL(2, 1) * a.Data[1][1] + M_EL(2, 2) * a.Data[2][1],
					M_EL(2, 0) * a.Data[0][2] + M_EL(2, 1) * a.Data[1][2] + M_EL(2, 2) * a.Data[2][2]
				)
			);
	}

	TEM_LOCAL_CLASS_TEMPLATE
	constexpr mat3<T> mat3<T>::operator+(const mat3<T>& a) const
	{
		return mat3<T>
			(
				vec3<T>(this->Data[0] + a.Data[0]),
				vec3<T>(this->Data[1] + a.Data[1]),
				vec3<T>(this->Data[2] + a.Data[2])
			);
	}

	TEM_LOCAL_CLASS_TEMPLATE
	constexpr mat3<T> mat3<T>::operator-(const mat3<T>& a) const
	{
		return mat3<T>
			(
				vec3<T>(this->Data[0] - a.Data[0]),
				vec3<T>(this->Data[1] - a.Data[1]),
				vec3<T>(this->Data[2] - a.Data[2])
			);
	}

	TEM_LOCAL_CLASS_TEMPLATE
	constexpr vec3<T> mat3<T>::operator*(const vec3<T>& a) const
	{
		return vec3<T>
			(
				M_EL(0,0) * a[0] + M_EL(0,1) * a[1] + M_EL(0,2) * a[2],
				M_EL(1,0) * a[0] + M_EL(1,1) * a[1] + M_EL(1,2) * a[2],
				M_EL(2,0) * a[0] + M_EL(2,1) * a[1] + M_EL(2,2) * a[2]
			);
	}

	TEM_LOCAL_CLASS_TEMPLATE
	constexpr vec3<T>& mat3<T>::operator[](const uint32_t Index)
	{
		return this->Data[Index];
	}

	TEM_LOCAL_CLASS_TEMPLATE
	constexpr const vec3<T>& mat3<T>::operator[](const uint32_t Index) const
	{
		return this->Data[Index];
	}

	TEM_LOCAL_CLASS_TEMPLATE
	constexpr const T* mat3<T>::getPtr() const
	{
		return reinterpret_cast<const T*>(this);
	}

	TEM_LOCAL_CLASS_TEMPLATE
	template<::tem::intern::temType U>
	constexpr mat3<T>::operator mat2<U>() const
	{
		return mat2<U>(
			static_cast<vec2<U>>(this->Data[0]),
			static_cast<vec2<U>>(this->Data[1])
		);
	}

	TEM_LOCAL_CLASS_TEMPLATE
	template<::tem::intern::temType U>
	constexpr mat3<T>::operator mat3<U>() const
	{
		return mat3<U>(
			static_cast<vec3<U>>(this->Data[0]),
			static_cast<vec3<U>>(this->Data[1]),
			static_cast<vec3<U>>(this->Data[2])
		);
	}

	TEM_LOCAL_CLASS_TEMPLATE
	constexpr mat3<T> mat3<T>::unitMatrix()
	{
		return mat3<T>(
			vec3<T>(static_cast<T>(1), static_cast<T>(0), static_cast<T>(0)),
			vec3<T>(static_cast<T>(0), static_cast<T>(1), static_cast<T>(0)),
			vec3<T>(static_cast<T>(0), static_cast<T>(0), static_cast<T>(1))
		);
	}
}

namespace tem::avx
{
	template class intern::mat3<tem_f32>;
	template class intern::mat3<tem_f64>;

	template class intern::mat3<tem_i8>;
	template class intern::mat3<tem_i16>;
	template class intern::mat3<tem_i32>;
	template class intern::mat3<tem_i64>;

	template class intern::mat3<tem_ui8>;
	template class intern::mat3<tem_ui16>;
	template class intern::mat3<tem_ui32>;
	template class intern::mat3<tem_ui64>;
}