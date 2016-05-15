#pragma once
//#include "../Macros/Macros.h"
#include <math.h>
#include "CU/Macros/Macros.h"

// Forward declarations
//
namespace CommonUtilities
{

	template<typename T>
	class Vector4;

	template<typename T>
	class Vector2;


	//
	// Vector3
	//

	template<typename T>
	class Vector3
	{
	public:		// Construction
				//
		Vector3(void);
		//Vector3( const Vector3 &aVector3 );
		explicit Vector3(const Vector2<T> &aVector2);
		explicit Vector3(const Vector4<T> &aVector4);
		template<typename U> explicit Vector3(const Vector3<U> &aVector);
		Vector3(const T anX, const T aY, const T aZ);


		// Arithmetic
		//

		friend Vector3 operator +(Vector3 aLeft, const Vector3 &aRight)
		{
			return aLeft += aRight;
		}


		friend Vector3 operator -(Vector3 aLeft, const Vector3 &aRight)
		{
			return aLeft -= aRight;
		}


		friend Vector3 operator *(Vector3 aLeft, const T aRight)
		{
			return aLeft *= aRight;
		}


		friend Vector3 operator /(Vector3 aLeft, const T aRight)
		{
			return aLeft /= aRight;
		}


		friend Vector3 operator -(Vector3 aRight)
		{
			aRight.x = -aRight.x;
			aRight.y = -aRight.y;
			aRight.z = -aRight.z;
			return aRight;
		}

		// Comparison //
		friend bool operator ==(const Vector3 &aLeft, const Vector3 &aRight)
		{
			return (aLeft.x == aRight.x && aLeft.y == aRight.y);
		}


		friend bool operator !=(const Vector3 &aLeft, const Vector3 &aRight)
		{
			return !(aLeft == aRight);
		}

		// Assignment
		//
		//Vector3 &operator =( const Vector3 &aRight );
		Vector3 &operator =(const Vector4<T> &aRight);
		Vector3 &operator =(const Vector2<T> &aRight);

		//// Combined
		////
		Vector3 &operator +=(const Vector3 &aRight);
		Vector3 &operator -=(const Vector3 &aRight);
		Vector3 &operator *=(const T aRight);
		Vector3 &operator /=(const T aRight);

		//// Info
		////
		T Length(void) const;
		T Length2(void) const;
		T Dot(const Vector3 &aRight) const;
		Vector3 Cross(const Vector3 &aRight) const;
		Vector3 GetNormalized(void) const;

		//// Manipulation
		////
		Vector3 &Normalize(void);

		union
		{
			T    x,
				u,
				r;
		};

		union
		{
			T    y,
				v,
				g;
		};

		union
		{
			T    z,
				w,
				b;
		};

		static T Dot(const Vector3 &aLeft, const Vector3 &aRight);
		static Vector3 Cross(const Vector3 aLeft, const Vector3 &aRight);
		static Vector3 Normalize(Vector3 aVector);

		static const Vector3	Zero,
			UnitX,
			UnitY,
			UnitZ,
			One;
			//DirectionVector45Deg;
	};

	using Vector3c = Vector3<char>;
	using Vector3i = Vector3<int>;
	using Vector3ui = Vector3<unsigned int>;
	using Vector3f = Vector3<float>;
	using Vector3d = Vector3<double>;

	template<typename TYPE>
	using Point3 = Vector3<TYPE>;

	using Point3c = Vector3<char>;
	using Point3i = Vector3<int>;
	using Point3ui = Vector3<unsigned int>;
	using Point3f = Vector3<float>;
	using Point3d = Vector3<double>;

	template<typename T> const Vector3<T> Vector3<T>::Zero(0, 0, 0);
	template<typename T> const Vector3<T> Vector3<T>::UnitX(1, 0, 0);
	template<typename T> const Vector3<T> Vector3<T>::UnitY(0, 1, 0);
	template<typename T> const Vector3<T> Vector3<T>::UnitZ(0, 0, 1);
	template<typename T> const Vector3<T> Vector3<T>::One(1, 1, 1);
	//template<typename T> const Vector3<T> Vector3<T>::DirectionVector45Deg(cos(DEGRESS_TO_RADIANSF(45)), sin(DEGRESS_TO_RADIANSF(45)), sin(DEGRESS_TO_RADIANSF(45)));
}
#include "vector3.inl"
