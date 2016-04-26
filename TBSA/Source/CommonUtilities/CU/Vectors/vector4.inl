
//#include "vector3.h"
namespace CommonUtilities
{

	template<typename T>
	inline Vector4<T>::Vector4(void)
	{
		x = static_cast<T>(0);
		y = static_cast<T>(0);
		z = static_cast<T>(0);
		w = static_cast<T>(0);
	}

	template<typename T>
	inline Vector4<T>::Vector4(const Vector3<T> &anOther)
	{
		(*this) = anOther;
	}

	template<typename T>
	inline Vector4<T> &Vector4<T>::operator =(const Vector3<T> &aRight)
	{
		x = aRight.x;
		y = aRight.y;
		z = aRight.z;
		w = static_cast<T>(1);

		return (*this);
	}



	template< typename T>
	template< typename U>
	inline Vector4<T>::Vector4(const Vector4<U> &aVector4)
	{
		this->x = static_cast<T>(aVector4.x);
		this->y = static_cast<T>(aVector4.y);
		this->z = static_cast<T>(aVector4.z);
		this->w = static_cast<T>(aVector4.w);
	}

	template<typename T>
	inline Vector4<T>::Vector4(const T anX, const T aY, const T aZ, const T aW)
	{
		x = anX;
		y = aY;
		z = aZ;
		w = aW;
	}

	template<typename T>
	inline Vector4<T> & Vector4<T>::operator +=(const Vector4 &aRight)
	{
		x += aRight.x;
		y += aRight.y;
		z += aRight.z;
		w += aRight.w;

		return (*this);
	}

	template<typename T>
	inline Vector4<T> & Vector4<T>::operator -=(const Vector4 &aRight)
	{
		x -= aRight.x;
		y -= aRight.y;
		z -= aRight.z;
		w -= aRight.w;

		return (*this);
	}

	template<typename T>
	inline Vector4<T> & Vector4<T>::operator *=(const T aRight)
	{
		x *= aRight;
		y *= aRight;
		z *= aRight;
		w *= aRight;

		return (*this);
	}

	template<typename T>
	inline Vector4<T> & Vector4<T>::operator /=(const T aRight)
	{
		x /= aRight;
		y /= aRight;
		z /= aRight;
		w /= aRight;

		return (*this);
	}

	template<typename T>
	inline T Vector4<T>::Length2(void) const
	{
		return ((x*x) + (y*y) + (z*z) + (w*w));
	}

	template<typename T>
	inline T Vector4<T>::Length(void) const
	{
		return sqrt(Length2());
	}

	template<typename T>
	inline T Vector4<T>::Dot(const Vector4 &aRight) const
	{
		return ((x * aRight.x) + (y * aRight.y) + (z * aRight.z) + (w * aRight.w));
	}

	template<typename T>
	inline Vector4<T> & Vector4<T>::Normalize(void)
	{
		const T TempLength = Length();
		x /= TempLength;
		y /= TempLength;
		z /= TempLength;
		w /= TempLength;

		return (*this);
	}

	template<typename T>
	inline Vector4<T> Vector4<T>::GetNormalized(void) const
	{
		Vector4 temp = (*this);
		return temp.Normalize();
	}

	template<typename T>
	inline T Vector4<T>::Dot(const Vector4 &aFirstVector, const Vector4 &aSecondVector)
	{
		return aFirstVector.Dot(aSecondVector);
	}

	template<typename T>
	inline Vector4<T> Vector4<T>::Normalize(Vector4 aVector)
	{
		return aVector.GetNormalized();
	}
}
///*
//
//
//
//
//
//// Assignment
////
//Vector4 &operator =( const Vector4 &aRight );
//
//// Compound assignment
////
//
//
//
//// Info
////
//
//
//
//
//// Manipulation
////
//
//
//static Vector4 Normalize( Vector4 aVector );
//
//
//Vector4(const Vector4 &aVector4);
//*/