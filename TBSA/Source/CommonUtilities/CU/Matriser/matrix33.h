#pragma once


#include "CU/Vectors/vector3.h"
#include "CU/Vectors/vector2.h"
#include <array>


// Forward declarations
//
namespace CommonUtilities
{

	template<typename T>
	class Matrix44;


	template<typename T>
	class Matrix33
	{
	public:     // Constants to avoid using magic numbers
				//
		static const unsigned int   NumRows = 3,
			NumColumns = 3,
			NumElements = NumRows * NumColumns;

		// Initializes the matrix to the identity matrix
		//
		Matrix33(void);

		// Initializes the matrix with the data from anOther
		//
		//Matrix33( const Matrix33 &anOther );

		// Initializes the matrix with the 3x3-part from anOther
		//
		Matrix33(const Matrix44<T> &anOther);

		// Initializes the matrix with the static_cast'ed data from anOther which uses another base type
		//
		template<typename U>
		Matrix33(const Matrix33<U> &anOther);

		// Initializes the matrix with the data from an array
		//
		// Explanation:
		// This allows the syntax: Matrix33 identity({1, 0, 0, 0, 1, 0, 0, 0, 1});
		//
		Matrix33(const T(&anArray)[NumElements]);

		// Initializes the matrix with plain values
		//
		Matrix33(
			const T a11, const T a12, const T a13,
			const T a21, const T a22, const T a23,
			const T a31, const T a32, const T a33);

		// Adds and assigns the values of aRight to this matrix
		//
		Matrix33 &operator +=(const Matrix33 &aRight);

		// Subtract and assigns the values of aRight to this matrix
		//
		Matrix33 &operator -=(const Matrix33 &aRight);

		// Multiplies this matrix with aRight
		//
		Matrix33 &operator *=(const Matrix33 &aRight);

		// Sets the values of this matrix to those of aRight
		//
		//Matrix33 &operator =( const Matrix33 &aRight );

		// Transposes the matrix and returns *this
		//
		Matrix33 &Transpose(void);

		// Creates a transformation matrix for rotating anAngle rad around the x-axis
		//
		static Matrix33 CreateRotateAroundX(const T anAngle);

		// Creates a transformation matrix for rotating anAngle rad around the y-axis
		//
		static Matrix33 CreateRotateAroundY(const T anAngle);

		// Creates a transformation matrix for rotating anAngle rad around the z-axis
		//
		static Matrix33 CreateRotateAroundZ(const T anAngle);

		// Returns a transposed copy of aMatrix
		//
		static Matrix33 Transpose(Matrix33 aMatrix);

		// The data of this matrix
		//

		Matrix33 &Rotate2D(const T aAngle);

		Matrix33 &Set2DRotation(const T aAngle);

		Vector2<T> GetPosition() const;

		Vector3<T> GetPosition3() const;

		void SetPosition(const Vector2<T> & aPosition);

		void SetPosition(const Vector3<T> & aPosition);

		T& operator()(const size_t aRow, const size_t aColumn);

		const T& GetDataAtPosition(const size_t aRow, const size_t aColumn) const;

#pragma warning( suppress : 4201 ) // NOTE: This works fine in VC2013 and GCC so I'm keeping it. //MAHAM
		union
		{
			struct
			{
				T    m11, m12, m13,
					m21, m22, m23,
					m31, m32, m33;
			};

			std::array<T, NumElements> myMatrix;
		};

		// Pre-created matrices
		//
		static const Matrix33   Identity,   // Identity matrix
			Zero;       // Matrix with all 0
	};

	template<typename T> const Matrix33<T> Matrix33<T>::Zero(0, 0, 0, 0, 0, 0, 0, 0, 0);
	template<typename T> const Matrix33<T> Matrix33<T>::Identity(1, 0, 0, 0, 1, 0, 0, 0, 1);
}

#include "matrix33.inl"

namespace CommonUtilities
{
	// Alias for Matrix33<float>. Add more if needed.
	//
	using Matrix33f = Matrix33<float>;


	// Returns a new matrix which is the sum of aLeft and aRight
	//
	template<typename T>
	Matrix33<T> operator +(Matrix33<T> aLeft, const Matrix33<T> &aRight)
	{
		return aLeft += aRight;
	}


	// Returns a new matrix wich is the difference of aLeft and aRight
	//
	template<typename T>
	Matrix33<T> operator -(Matrix33<T> aLeft, const Matrix33<T> &aRight)
	{
		return aLeft -= aRight;
	}


	// Returns a new matrix which is the product of aLeft and aRight
	//
	template<typename T>
	Matrix33<T> operator *(Matrix33<T> aLeft, const Matrix33<T> &aRight)
	{
		return aLeft *= aRight;
	}


	template<typename T>
	inline void operator*=(Vector3<T> &aVector, const Matrix33<T> &aMatrix)
	{
		aVector = aVector * aMatrix;
	}

	// Returns a new matrix which is the product of the vector aLeft and the matrix aRight
	//
	template<typename T>
	Vector3<T> operator *(Vector3<T> aLeft, const Matrix33<T> &aRight)
	{
		Vector3<T> resultVector;

		resultVector.x = (aLeft.x * aRight.m11) + (aLeft.y * aRight.m21) + (aLeft.z * aRight.m31);

		resultVector.y = (aLeft.x * aRight.m12) + (aLeft.y * aRight.m22) + (aLeft.z * aRight.m32);

		resultVector.z = (aLeft.x * aRight.m13) + (aLeft.y * aRight.m23) + (aLeft.z * aRight.m33);

		return resultVector;
	}

	template<typename T>
	Vector2<T> operator *(Vector2<T> aLeft, const Matrix33<T> &aRight)
	{
		Vector2<T> resultVector;

		resultVector.x = (aLeft.x * aRight.m11) + (aLeft.y * aRight.m21) + (static_cast<T>(1) * aRight.m31);

		resultVector.y = (aLeft.x * aRight.m12) + (aLeft.y * aRight.m22) + (static_cast<T>(1) * aRight.m32);

		return resultVector;
	}


	// Compares aLeft and aRight componentwise
	//
	template<typename T>
	bool operator ==(const Matrix33<T> &aLeft, const Matrix33<T> &aRight)
	{
		for (size_t iArraySlot = 0; iArraySlot < aRight.NumElements; ++iArraySlot)
		{
			if (aLeft.myMatrix[iArraySlot] != aRight.myMatrix[iArraySlot])
			{
				return false;
			}
		}
		return true;
	}


	// Returns the negated result of aLeft == aRight
	//
	template<typename T>
	bool operator !=(const Matrix33<T> &aLeft, const Matrix33<T> &aRight)
	{
		return !(aLeft == aRight);
	}

}