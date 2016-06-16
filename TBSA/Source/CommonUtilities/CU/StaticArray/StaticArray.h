#pragma once
#include <cassert>

namespace CommonUtilities
{
	template <typename Type, int Size>
	class StaticArray
	{
	public:
		StaticArray();
		~StaticArray();

		inline const Type& operator[](const int& aIndex) const;
		inline Type& operator[](const int& aIndex);

		// Utility functions
		inline int GetSize();
		inline void Insert(int aIndex, Type& aObject);
		inline void DeleteAll();

	private:
		Type myData[Size];
		int mySize = Size - 1;
	};

	template <typename Type, int Size>
	int CommonUtilities::StaticArray<Type, Size>::GetSize()
	{
		return mySize;
	}

	template <typename Type, int Size>
	StaticArray<Type, Size>::StaticArray()
	{
	}

	template <typename Type, int Size>
	StaticArray<Type, Size>::~StaticArray()
	{
	}

	template <typename Type, int Size>
	const Type& StaticArray<Type, Size>::operator[](const int& aIndex) const
	{
		assert(aIndex <= mySize && "Index is out of range");
		assert(aIndex >= 0 && "Index can not be a negative number");

		return myData[aIndex];
	}

	template <typename Type, int Size>
	Type& StaticArray<Type, Size>::operator[](const int& aIndex)
	{
		assert(aIndex <= mySize && "Index is out of range");
		assert(aIndex >= 0 && "Index can not be a negative number");

		return myData[aIndex];
	}

	template <typename Type, int Size>
	void StaticArray<Type, Size>::Insert(int aIndex, Type& aObject)
	{
		assert(aIndex <= mySize && "Index is out of range");
		assert(aIndex >= 0 && "Index can not be a negative number");


		if (aIndex != mySize)
		{
			for (size_t iData = static_cast<size_t>(mySize); iData > static_cast<size_t>(aIndex); --iData)
			{
				myData[iData] = myData[iData - 1];
			}
		}

		myData[aIndex] = aObject;
	}

	template <typename Type, int Size>
	void StaticArray<Type, Size>::DeleteAll()
	{
		for (size_t iSlot = 0; iSlot <= static_cast<size_t>(mySize); ++iSlot)
		{
			delete myData[iSlot];
			myData[iSlot] = nullptr;
		}
	}
}