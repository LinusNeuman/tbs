#pragma once
#include "CU/GrowingArray/GrowingArray.h"

namespace CommonUtilities
{

	template <typename T, typename CountType = unsigned short>
	class GridArray
	{
	public:
		GridArray(CountType aWidth, CountType aHeight, const bool aRunConstructors = true);
		//GridArray(const Vector2<CountType> & aWidthAndHeight, const bool aRunConstructors = true);

		void SetSizeClear(CountType aWidth, CountType aHeight, const bool aClearFlag = true);
		//void SetSizeClear(const Vector2<CountType> & aWidthAndHeight, const bool aClearFlag = true);

		inline T & Access(const CountType& aX, const CountType& aY);
		inline const T Access(const CountType& aX, const CountType& aY) const;

		/*inline T & Access(const Vector2<CountType> & aXY);
		inline const T Access(const Vector2<CountType> & aXY) const;*/

		inline void Optimize();
		__forceinline CountType Width() const;
		__forceinline CountType Height() const;

	private:

		CommonUtilities::GrowingArray<T, CountType> myArray;
		CountType myWidth;
		CountType myHeight;
	};

	//template <typename T, typename CountType /*= unsigned short*/>
	//GridArray<T, CountType>::GridArray(const Vector2<CountType> & aWidthAndHeight, const bool aRunConstructors/* = true*/) :
	//	myArray(aWidthAndHeight.x * aWidthAndHeight.y)
	//{
	//	SetSizeClear(aWidthAndHeight, aRunConstructors);
	//}

	template <typename T, typename CountType /*= unsigned short*/>
	void GridArray<T, CountType>::Optimize()
	{
		myArray.Optimize();
	}

	template <typename T, typename CountType /*= unsigned short*/>
	GridArray<T, CountType>::GridArray(CountType aWidth, CountType aHeight, const bool aRunConstructors/* = true*/) :
		myArray(aWidth * aHeight)
	{
		SetSizeClear(aWidth, aHeight, aRunConstructors);
	}

	template <typename T, typename CountType /*= unsigned short*/>
	void GridArray<T, CountType>::SetSizeClear(CountType aWidth, CountType aHeight, const bool aClearFlag/* = false*/)
	{
		myWidth = aWidth;
		myHeight = aHeight;
		myArray.Resize(myWidth * myHeight);

		if (aClearFlag == true)
		{
			for (CountType iSlot = 0; iSlot < myArray.Size(); ++iSlot)
			{
				myArray[iSlot] = T();
			}
		}
	}

	template <typename T, typename CountType /*= unsigned short*/>
	T & GridArray<T, CountType>::Access(const CountType& aX, const CountType& aY)
	{
		DL_ASSERT(((aX * myWidth) + aY) < myArray.Size(), "Trying to access GridArrayPosition that is out of range");
		return myArray[(aX * myWidth) + aY];
	}

	template <typename T, typename CountType /*= unsigned short*/>
	const T GridArray<T, CountType>::Access(const CountType& aX, const CountType& aY) const
	{
		return myArray[(aX * myWidth) + aY];
	}

	//template <typename T, typename CountType /*= unsigned short*/>
	//const T GridArray<T, CountType>::Access(const Vector2<CountType> & aXY) const
	//{
	//	return Access(aXY.x, aXY.y);
	//}

	//template <typename T, typename CountType /*= unsigned short*/>
	//T & GridArray<T, CountType>::Access(const Vector2<CountType> & aXY)
	//{
	//	return Access(aXY.x, aXY.y);
	//}

	//template <typename T, typename CountType /*= unsigned short*/>
	//void GridArray<T, CountType>::SetSizeClear(const Vector2<CountType> & aWidthAndHeight, const bool aClearFlag /*= true*/)
	//{
	//	SetSizeClear(aWidthAndHeight.x, aWidthAndHeight.y, aClearFlag);
	//}

	template <typename T, typename CountType /*= unsigned short*/>
	CountType GridArray<T, CountType>::Height() const
	{
		return myHeight;
	}

	template <typename T, typename CountType /*= unsigned short*/>
	CountType GridArray<T, CountType>::Width() const
	{
		return myWidth;
	}

}