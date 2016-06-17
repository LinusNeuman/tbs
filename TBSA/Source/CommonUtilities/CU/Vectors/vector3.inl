
#include "CU/Vectors/vector4.h"
#include "CU/Vectors/vector2.h"

namespace CommonUtilities
{

	template<typename T>
	inline Vector3<T>::Vector3(void)
	{
		x = static_cast<T>(0);
		y = static_cast<T>(0);
		z = static_cast<T>(0);
	}


	template<typename T>
	inline Vector3<T>::Vector3(const Vector2<T> &aVector2)
	{
		(*this) = aVector2;
	}

	template<typename T>
	inline Vector3<T>::Vector3(const Vector4<T> &aVector4)
	{
		(*this) = aVector4;
	}

	template< typename T>
	template< typename U>
	inline Vector3<T>::Vector3(const Vector3<U> &aVector3)
	{
		this->x = static_cast<T>(aVector3.x);
		this->y = static_cast<T>(aVector3.y);
		this->z = static_cast<T>(aVector3.z);
	}

	template<typename T>
	inline Vector3<T>::Vector3(const T anX, const T aY, const T aZ)
	{
		x = anX;
		y = aY;
		z = aZ;
	}


	template<typename T>
	inline Vector3<T> & Vector3<T>::operator =(const Vector4<T> &aRight)
	{
		x = aRight.x;
		y = aRight.y;
		z = aRight.z;

		return (*this);
	}

	template<typename T>
	inline Vector3<T> & Vector3<T>::operator =(const Vector2<T> &aRight)
	{
		x = aRight.x;
		y = aRight.y;
		z = static_cast<T>(1);

		return (*this);
	}

	template<typename T>
	inline Vector3<T> & Vector3<T>::operator +=(const Vector3 &aRight)
	{
		x += aRight.x;
		y += aRight.y;
		z += aRight.z;

		return (*this);
	}

	template<typename T>
	inline Vector3<T> & Vector3<T>::operator -=(const Vector3 &aRight)
	{
		x -= aRight.x;
		y -= aRight.y;
		z -= aRight.z;

		return (*this);
	}

	template<typename T>
	inline Vector3<T> & Vector3<T>::operator *=(const T aRight)
	{
		x *= aRight;
		y *= aRight;
		z *= aRight;

		return (*this);
	}

	template<typename T>
	inline Vector3<T> & Vector3<T>::operator /=(const T aRight)
	{
		x /= aRight;
		y /= aRight;
		z /= aRight;

		return (*this);
	}

	template<typename T>
	inline T Vector3<T>::Length2(void) const
	{
		return ((x*x) + (y*y) + (z*z));
	}

	template<typename T>
	T Vector3<T>::Length(void) const
	{
		return sqrt(Length2());
	}

	template<typename T>
	inline T Vector3<T>::Dot(const Vector3 &aRight) const
	{
		return ((x * aRight.x) + (y * aRight.y) + (z * aRight.z));
	}

	template<typename T>
	inline Vector3<T> & Vector3<T>::Normalize(void)
	{
		const T TempLength = Length();
		x /= TempLength;
		y /= TempLength;
		z /= TempLength;

		return (*this);
	}

	template<typename T>
	inline Vector3<T> Vector3<T>::Cross(const Vector3 &aRight) const
	{
		Vector3 temp = aRight;

		temp.x = (y * aRight.z) - (z * aRight.y);
		temp.y = (z * aRight.x) - (x * aRight.z);
		temp.z = (x * aRight.y) - (y * aRight.x);

		return temp;
	}


	template<typename T>
	inline Vector3<T> Vector3<T>::GetNormalized(void) const
	{
		Vector3 temp = (*this);
		return temp.Normalize();
	}

	template<typename T>
	inline T Vector3<T>::Dot(const Vector3 &aFirstVector, const Vector3 &aSecondVector)
	{
		return aFirstVector.Dot(aSecondVector);
	}

	template<typename T>
	inline Vector3<T> Vector3<T>::Normalize(Vector3 aVector)
	{
		return aVector.GetNormalized();
	}

	template<typename T>
	inline Vector3<T> Vector3<T>::Cross(const Vector3 aLeft, const Vector3 &aRight)
	{
		return aLeft.Cross(aRight);
	}
	/*





	// Assignment
	//
	Vector3 &operator =( const Vector3 &aRight );

	// Compound assignment
	//



	// Info
	//




	// Manipulation
	//


	static Vector3 Normalize( Vector3 aVector );


	Vector3(const Vector3 &aVector3);
	*/;
}