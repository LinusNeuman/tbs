#pragma once


#include "../Vectors/vector4.h"
#include "../Vectors/vector3.h"
#include <array>


// Forward declarations
//
namespace CommonUtilities
{

	template<typename T>
	class Matrix33;


	template<typename T>
	class Matrix44
	{
	public:     // Constant to avoid using magic numbers
				//
		static const unsigned int   NumRows = 4,
			NumColumns = 4,
			NumElements = NumRows * NumColumns;

		// Initializes the matrix to the identity matrix
		//
		Matrix44(void);

		/*// Initializes the matrix with the data from anOther
		//
//			Matrix44( const Matrix44 &anOther );
//
//			// Initializes the matrix with anOther's data as the top left 3x3-part and sets the
//			// rest of the matrix like the identity matrix
//			//*/
		Matrix44(const Matrix33<T> &anOther);
		//
					// Initializes the matrix with the static_cast'ed data from anOther
					//
		template<typename U>
		Matrix44(const Matrix44<U> &anOther);
		//
		//			// Initializes the matrix with the data from an array
		//			//
		Matrix44(const T(&anArray)[NumElements]);
		//
		//			// Initializes the matrix with plain values
		//			//
		Matrix44(
			const T a11, const T a12, const T a13, const T a14,
			const T a21, const T a22, const T a23, const T a24,
			const T a31, const T a32, const T a33, const T a34,
			const T a41, const T a42, const T a43, const T a44);
		//
		//			// Adds and assigns the values of aRight to this matrix
		//			//
		Matrix44 &operator +=(const Matrix44 &aRight);
		//
		//			// Subtract and assigns the values of aRight to this matrix
		//			//
		Matrix44 &operator -=(const Matrix44 &aRight);
		//
		//			// Multiplies this matrix with aRight
		//			//
		Matrix44 &operator *=(const Matrix44 &aRight);
		//
		//			// Sets the values of this matrix to those of aRight
		//			//
		//			Matrix44 &operator =( const Matrix44 &aRight );
		//
		//			// Returns a transposed copy of this matrix
		//			//
		Matrix44 &Transpose(void);
		//
		//			// Creates a transformation matrix for rotating anAngle rad around the x-axis
		//			//
		static Matrix44 CreateRotateAroundX(const T anAngle);
		//
		//			// Creates a transformation matrix for rotating anAngle rad around the y-axis
		//			//
		static Matrix44 CreateRotateAroundY(const T anAngle);
		//
		//			// Creates a transformation matrix for rotating anAngle rad around the z-axis
		//			//
		static Matrix44 CreateRotateAroundZ(const T anAngle);
		//
		//			// Returns a transposed copy of aMatrix
		//			//
		static Matrix44 Transpose(Matrix44 aMatrix);
		//
		//			// The data of this matrix
		//			//

		Vector3<T> GetPosition() const;

		Vector4<T> GetPosition4() const;

		void SetPosition(const Vector3<T> & aPosition);

		void SetPosition(const Vector4<T> & aPosition);

		Matrix44<T> GetInverse(void) const;

		T& operator()(const size_t aRow, const size_t aColumn);

		const T& GetDataAtPosition(const size_t aRow, const size_t aColumn) const;

		static Matrix44 CreateProjectionMatrixLH(T aNearZ, T aFarZ, T aAspectRatio, T aFovAngle);

		Vector3<T> GetRight() const;

		Vector3<T> GetUp() const;

		Vector3<T> GetForward() const;


#pragma warning( suppress : 4201 ) // NOTE: This works fine in VC2013 and GCC so I'm keeping it. //MAHAM
		union
		{
			struct
			{
				T    m11, m12, m13, m14,
					m21, m22, m23, m24,
					m31, m32, m33, m34,
					m41, m42, m43, m44;
			};

			std::array<T, NumElements> myMatrix;

			/*struct
			{
				Vector4<T> myFirstRow;
				Vector4<T> mySecondRow;
				Vector4<T> myThirdRow;
				Vector4<T> myFourthRow;
			};

			std::array<Vector4<T>, NumRows> myVectorRows;*/
		};

		// Pre-created identity matrix
		//
		static const Matrix44   Identity,
			Zero;
	};

	template<typename T> const Matrix44<T> Matrix44<T>::Zero(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
	template<typename T> const Matrix44<T> Matrix44<T>::Identity(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1);
}

#include "matrix44.inl"

namespace CommonUtilities
{

	using Matrix44f = Matrix44<float>;


	// Returns a new matrix which is the sum of aLeft and aRight
	//
	template<typename T>
	Matrix44<T> operator +(Matrix44<T> aLeft, const Matrix44<T> &aRight)
	{
		return aLeft += aRight;
	}


	// Returns a new matrix wich is the difference of aLeft and aRight
	//
	template<typename T>
	Matrix44<T> operator -(Matrix44<T> aLeft, const Matrix44<T> &aRight)
	{
		return aLeft -= aRight;
	}


	// Returns a new matrix which is the product of aLeft and aRight
	//
	template<typename T>
	Matrix44<T> operator *(Matrix44<T> aLeft, const Matrix44<T> &aRight)
	{
		return aLeft *= aRight;
	}


	// Returns a new matrix which is the product of the vector aLeft and the matrix aRight
	//
	template<typename T>
	Vector4<T> operator *(Vector4<T> aLeft, const Matrix44<T> &aRight)
	{
		Vector4<T> resultVector;

		resultVector.x = (aLeft.x * aRight.m11) + (aLeft.y * aRight.m21) + (aLeft.z * aRight.m31) + (aLeft.w * aRight.m41);

		resultVector.y = (aLeft.x * aRight.m12) + (aLeft.y * aRight.m22) + (aLeft.z * aRight.m32) + (aLeft.w * aRight.m42);

		resultVector.z = (aLeft.x * aRight.m13) + (aLeft.y * aRight.m23) + (aLeft.z * aRight.m33) + (aLeft.w * aRight.m43);

		resultVector.w = (aLeft.x * aRight.m14) + (aLeft.y * aRight.m24) + (aLeft.z * aRight.m34) + (aLeft.w * aRight.m44);

		return resultVector;
	}

	template<typename T>
	Vector3<T> operator *(Vector3<T> aLeft, const Matrix44<T> &aRight)
	{
		Vector3<T> resultVector;

		resultVector.x = (aLeft.x * aRight.m11) + (aLeft.y * aRight.m21) + (aLeft.z * aRight.m31) + (static_cast<T>(1) * aRight.m41);

		resultVector.y = (aLeft.x * aRight.m12) + (aLeft.y * aRight.m22) + (aLeft.z * aRight.m32) + (static_cast<T>(1) * aRight.m42);

		resultVector.z = (aLeft.x * aRight.m13) + (aLeft.y * aRight.m23) + (aLeft.z * aRight.m33) + (static_cast<T>(1) * aRight.m43);

		return resultVector;
	}

	// Compares aLeft and aRight componentwise
	//
	template<typename T>
	bool operator ==(const Matrix44<T> &aLeft, const Matrix44<T> &aRight)
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
	bool operator !=(const Matrix44<T> &aLeft, const Matrix44<T> &aRight)
	{
		return !(aLeft == aRight);
	}

}