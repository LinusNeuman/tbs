
#include <cmath>

namespace CommonUtilities
{

	template<typename T>
	inline Vector2<T>::Vector2(void)
	{
		x = static_cast<T>(0);
		y = static_cast<T>(0);
	}

	template< typename T>
	template< typename U>
	inline Vector2<T>::Vector2(const Vector2<U> &aVector2)
	{
		this->x = static_cast<T>(aVector2.x);
		this->y = static_cast<T>(aVector2.y);
	}

	template<typename T>
	inline Vector2<T>::Vector2(const T anX, const T aY)
	{
		x = anX;
		y = aY;
	}

	template<typename T>
	inline Vector2<T> & Vector2<T>::operator +=(const Vector2 &aRight)
	{
		x += aRight.x;
		y += aRight.y;

		return (*this);
	}

	template<typename T>
	inline Vector2<T> & Vector2<T>::operator -=(const Vector2 &aRight)
	{
		x -= aRight.x;
		y -= aRight.y;

		return (*this);
	}

	template<typename T>
	inline Vector2<T> & Vector2<T>::operator *=(const T aRight)
	{
		x *= aRight;
		y *= aRight;

		return (*this);
	}

	template<typename T>
	inline Vector2<T> & Vector2<T>::operator /=(const T aRight)
	{
		x /= aRight;
		y /= aRight;

		return (*this);
	}

	template<typename T>
	inline T Vector2<T>::Length2(void) const
	{
		return ((x*x) + (y*y));
	}

	template<typename T>
	inline T Vector2<T>::Length(void) const
	{
		return sqrt(Length2());
	}

	template<typename T>
	inline T Vector2<T>::Dot(const Vector2 &aRight) const
	{
		return ((x * aRight.x) + (y * aRight.y));
	}

	template<typename T>
	inline Vector2<T> & Vector2<T>::Normalize(void)
	{
		const T TempLength = Length();
		if (TempLength != 0)
		{
			x /= TempLength;
			y /= TempLength;
		}
		else
		{
			x = 0;
			y = 0;
		}

		return (*this);
	}

	template<typename T>
	inline Vector2<T> Vector2<T>::GetNormalized(void) const
	{
		Vector2 temp = (*this);
		return temp.Normalize();
	}

	template<typename T>
	inline T Vector2<T>::Dot(const Vector2 &aFirstVector, const Vector2 &aSecondVector)
	{
		return aFirstVector.Dot(aSecondVector);
	}

	template<typename T>
	inline Vector2<T> Vector2<T>::Normalize(Vector2 aVector)
	{
		return aVector.GetNormalized();
	}

	template<typename T>
	inline T Vector2<T>::GetAngle() const
	{
		//return static_cast<T>(acos(x / Length()));
		return static_cast<float>(atan2(y, x));
	}

}
/*





// Assignment
//
Vector2 &operator =( const Vector2 &aRight );

// Compound assignment
//



// Info
//




// Manipulation
//


static Vector2 Normalize( Vector2 aVector );


Vector2(const Vector2 &aVector2);
*/