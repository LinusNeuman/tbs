#pragma once


// Forward declarations
//
namespace CommonUtilities
{
	template<typename T>
	class Vector3;


	template<typename T>
	class Vector4
	{
	public:		// Construction
				//
		Vector4(void);
		//Vector4( const Vector4 &anOther );
		explicit Vector4(const Vector3<T> &anOther);
		template<typename U> explicit Vector4(const Vector4<U> &anOther);
		Vector4(const T anX, const T anY, const T aZ, const T aW);

		// Arithmetic
		//
		friend Vector4 operator +(Vector4 aLeft, const Vector4 &aRight)
		{
			return aLeft += aRight;
		}


		friend Vector4 operator -(Vector4 aLeft, const Vector4 &aRight)
		{
			return aLeft -= aRight;
		}

		friend bool operator <(Vector4 aLeft, const Vector4 &aRight)
		{
			return (aLeft.Length() < aRight.Length());
		}


		friend Vector4 operator *(Vector4 aLeft, const T aRight)
		{
			return aLeft *= aRight;
		}


		friend Vector4 operator /(Vector4 aLeft, const T aRight)
		{
			return aLeft /= aRight;
		}


		friend Vector4 operator -(Vector4 aRight)
		{
			aRight.x = -aRight.x;
			aRight.y = -aRight.y;
			aRight.z = -aRight.z;
			aRight.w = -aRight.w;
			return aRight;
		}

		// Comparison //
		friend bool operator ==(const Vector4 &aLeft, const Vector4 &aRight)
		{
			return (aLeft.x == aRight.x && aLeft.y == aRight.y && aLeft.z == aRight.z && aLeft.w == aRight.w);
		}


		friend bool operator !=(const Vector4 &aLeft, const Vector4 &aRight)
		{
			return !(aLeft == aRight);
		}


		// Assignment
		//
		//Vector4 &operator =( const Vector4 &aRight );
		Vector4 &operator =(const Vector3<T> &aRight);

		//// Combined
		////
		Vector4 &operator +=(const Vector4 &aRight);
		Vector4 &operator -=(const Vector4 &aRight);
		Vector4 &operator *=(const T aRight);
		Vector4 &operator /=(const T aRight);

		//// Info
		////
		T Length(void) const;
		T Length2(void) const;
		T Dot(const Vector4 &aRight) const;
		Vector4 GetNormalized(void) const;

		//// Manipulation
		////
		Vector4 &Normalize(void);

		union
		{
			T    x,
				r;
		};

		union
		{
			T    y,
				g;
		};

		union
		{
			T    z,
				b,
			Width;
		};

		union
		{
			T    w,
				a,
			Height;
		};

		static Vector4 Normalize(Vector4 aVector);
		static T Dot(const Vector4 &aFirstVector, const Vector4 &aSecondVector);

		static const Vector4	Zero,
			UnitX,
			UnitY,
			UnitZ,
			UnitW,
			One;
	};

	using Vector4c = Vector4<char>;
	using Vector4i = Vector4<int>;
	using Vector4ui = Vector4<unsigned int>;
	using Vector4f = Vector4<float>;
	using Vector4d = Vector4<double>;

	using Point4c = Vector4<char>;
	using Point4i = Vector4<int>;
	using Point4ui = Vector4<unsigned int>;
	using Point4f = Vector4<float>;
	using Point4d = Vector4<double>;

	template<typename T> const Vector4<T> Vector4<T>::Zero(0, 0, 0, 0);
	template<typename T> const Vector4<T> Vector4<T>::UnitX(1, 0, 0, 0);
	template<typename T> const Vector4<T> Vector4<T>::UnitY(0, 1, 0, 0);
	template<typename T> const Vector4<T> Vector4<T>::UnitZ(0, 0, 1, 0);
	template<typename T> const Vector4<T> Vector4<T>::UnitW(0, 0, 0, 1);
	template<typename T> const Vector4<T> Vector4<T>::One(1, 1, 1, 1);



}

#include "vector4.inl"