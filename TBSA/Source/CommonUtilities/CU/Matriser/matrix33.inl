
namespace CommonUtilities
{

	template<typename T>
	Matrix33<T>::Matrix33(void)
	{
		m11 = static_cast<T>(1);
		m12 = static_cast<T>(0);
		m13 = static_cast<T>(0);

		m21 = static_cast<T>(0);
		m22 = static_cast<T>(1);
		m23 = static_cast<T>(0);

		m31 = static_cast<T>(0);
		m32 = static_cast<T>(0);
		m33 = static_cast<T>(1);
	}

	template<typename T>
	template<typename U>
	Matrix33<T>::Matrix33(const Matrix33<U> &anOther)
	{
		m11 = static_cast<T>(anOther.m11);
		m12 = static_cast<T>(anOther.m12);
		m13 = static_cast<T>(anOther.m13);

		m21 = static_cast<T>(anOther.m21);
		m22 = static_cast<T>(anOther.m22);
		m23 = static_cast<T>(anOther.m23);

		m31 = static_cast<T>(anOther.m31);
		m32 = static_cast<T>(anOther.m32);
		m33 = static_cast<T>(anOther.m33);

	}

	template<typename T>
	Matrix33<T>::Matrix33(const T(&anArray)[NumElements])
	{
		for (size_t iArraySlot = 0; iArraySlot < NumElements; ++iArraySlot)
		{
			myMatrix[iArraySlot] = anArray[iArraySlot];
		}
	}

	template<typename T>
	Matrix33<T>::Matrix33(
		const T a11, const T a12, const T a13,
		const T a21, const T a22, const T a23,
		const T a31, const T a32, const T a33)
	{
		m11 = a11;
		m12 = a12;
		m13 = a13;

		m21 = a21;
		m22 = a22;
		m23 = a23;


		m31 = a31;
		m32 = a32;
		m33 = a33;
	}


	template<typename T>
	Matrix33<T> & Matrix33<T>::operator +=(const Matrix33 &aRight)
	{
		for (size_t iArraySlot = 0; iArraySlot < NumElements; ++iArraySlot)
		{
			myMatrix[iArraySlot] += aRight.myMatrix[iArraySlot];
		}

		return (*this);
	}

	template<typename T>
	Matrix33<T> & Matrix33<T>::operator -=(const Matrix33 &aRight)
	{
		for (size_t iArraySlot = 0; iArraySlot < NumElements; ++iArraySlot)
		{
			myMatrix[iArraySlot] -= aRight.myMatrix[iArraySlot];
		}

		return (*this);
	}


	template<typename T>
	Matrix33<T> & Matrix33<T>::operator *=(const Matrix33 &aRight)
	{

		std::array<T, NumElements> tempMatrix;

		for (size_t iColumnPos = 0; iColumnPos < NumColumns; ++iColumnPos)
		{
			for (size_t iRowPos = 0; iRowPos < NumRows; ++iRowPos)
			{
				T result = 0;

				for (size_t iPos = 0; iPos < NumRows; ++iPos)
				{
					result += GetDataAtPosition(iPos + 1, iColumnPos + 1) * aRight.GetDataAtPosition((iRowPos + 1), iPos + 1);
				}

				tempMatrix[((iColumnPos * NumColumns) + iRowPos)] = result;
			}
		}

		myMatrix = tempMatrix;

		return (*this);
	}

	template<typename T>
	T& Matrix33<T>::operator()(const size_t aRow, const size_t aColumn)
	{
		return myMatrix[(((aColumn - 1) * NumColumns) + (aRow - 1))];
	}

	template<typename T>
	const T& Matrix33<T>::GetDataAtPosition(const size_t aRow, const size_t aColumn) const
	{
		return myMatrix[(((aColumn - 1) * NumColumns) + (aRow - 1))];
	}

	template<typename T>
	Matrix33<T> & Matrix33<T>::Transpose(void)
	{
		std::array<T, NumElements> tempMatrix;

		for (size_t iColumnPos = 0; iColumnPos < NumColumns; ++iColumnPos)
		{
			for (size_t iRowPos = 0; iRowPos < NumRows; ++iRowPos)
			{

				tempMatrix[((iColumnPos * NumColumns) + iRowPos)] = (*this)(iColumnPos + 1, iRowPos + 1);
			}
		}

		myMatrix = tempMatrix;

		return (*this);
	}


	template<typename T>
	Matrix33<T> Matrix33<T>::CreateRotateAroundX(const T anAngle)
	{
		return Matrix33(
			static_cast<T>(1), static_cast<T>(0), static_cast<T>(0),
			static_cast<T>(0), static_cast<T>(cos(anAngle)), static_cast<T>(sin(anAngle)),
			static_cast<T>(0), static_cast<T>(-sin(anAngle)), static_cast<T>(cos(anAngle))
			);
	}

	template<typename T>
	Matrix33<T> Matrix33<T>::CreateRotateAroundY(const T anAngle)
	{
		return Matrix33(
			static_cast<T>(cos(anAngle)), static_cast<T>(0), static_cast<T>(-sin(anAngle)),
			static_cast<T>(0), static_cast<T>(1), static_cast<T>(0),
			static_cast<T>(sin(anAngle)), static_cast<T>(0), static_cast<T>(cos(anAngle))
			);
	}

	template<typename T>
	Matrix33<T> Matrix33<T>::CreateRotateAroundZ(const T anAngle)
	{
		return Matrix33(
			static_cast<T>(cos(anAngle)), static_cast<T>(sin(anAngle)), static_cast<T>(0),
			static_cast<T>(-sin(anAngle)), static_cast<T>(cos(anAngle)), static_cast<T>(0),
			static_cast<T>(0), static_cast<T>(0), static_cast<T>(1)
			);
	}

	template<typename T>
	Matrix33<T> & Matrix33<T>::Set2DRotation(const T aAngle)
	{
		m11 = static_cast<T>(cos(aAngle)); m12 = static_cast<T>(sin(aAngle));
		m21 = static_cast<T>(-sin(aAngle)); m22 = static_cast<T>(cos(aAngle));

		return (*this);
	}

	template<typename T>
	Matrix33<T> & Matrix33<T>::Rotate2D(const T aAngle)
	{
		Vector2<T> tempPosition(GetPosition());

		SetPosition(Vector2<T>(0, 0));

		(*this) *= CreateRotateAroundZ(aAngle);

		SetPosition(tempPosition);

		return (*this);
	}

	template<typename T>
	Matrix33<T> Matrix33<T>::Transpose(Matrix33 aMatrix)
	{
		Matrix33 copy(aMatrix);

		return copy.Transpose();
	}

	template<typename T>
	Matrix33<T>::Matrix33(const Matrix44<T> &anOther)
	{
		m11 = anOther.m11;
		m12 = anOther.m12;
		m13 = anOther.m13;

		m21 = anOther.m21;
		m22 = anOther.m22;
		m23 = anOther.m23;

		m31 = anOther.m31;
		m32 = anOther.m32;
		m33 = anOther.m33;
	}

	template<typename T>
	Vector2<T> Matrix33<T>::GetPosition() const
	{
		return Vector2<T>(m31, m32);
	}

	template<typename T>
	Vector3<T> Matrix33<T>::GetPosition3() const
	{
		return Vector3<T>(m31, m32, m33);
	}

	template<typename T>
	void Matrix33<T>::SetPosition(const Vector2<T> & aPosition)
	{
		m31 = aPosition.x;
		m32 = aPosition.y;
	}

	template<typename T>
	void Matrix33<T>::SetPosition(const Vector3<T> & aPosition)
	{
		m31 = aPosition.x;
		m32 = aPosition.y;
		m33 = aPosition.z;
	}
}