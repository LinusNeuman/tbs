#pragma once
#include <cassert>
#include <cstring>

namespace CommonUtilities
{
	template <typename Type, int Capacity, typename CountType = unsigned short, bool UseSafeModeFlag = true>
	class VectorOnStack
	{
	public:
		VectorOnStack();
		VectorOnStack(const VectorOnStack& aVectorOnStack);

		~VectorOnStack();

		VectorOnStack & operator=(const VectorOnStack & aVectorOnStack);

		inline const Type& operator[](const CountType & aIndex) const;
		inline Type& operator[](const CountType & aIndex);

		inline void Add(const Type& aObject);
		inline void Insert(CountType aIndex, Type& aObject);
		inline void DeleteCyclic(Type& aObject);
		inline void DeleteCyclicAtIndex(CountType aItemNumber);
		inline void RemoveCyclic(const Type& aObject);
		inline void RemoveCyclicAtIndex(CountType aItemNumber);

		inline void Clear();
		inline void DeleteAll();

		__forceinline CountType Size() const;

	private:
		Type myData[Capacity];
		int mySize = Capacity - 1;
		CountType myEnd = 0;
	};

	template <typename Type, int Capacity, typename CountType, bool UseSafeModeFlag>
	VectorOnStack<Type, Capacity, CountType, UseSafeModeFlag>::VectorOnStack()
	{
	}

	template <typename Type, int Capacity, typename CountType, bool UseSafeModeFlag>
	VectorOnStack<Type, Capacity, CountType, UseSafeModeFlag>::VectorOnStack(const VectorOnStack& aVectorOnStack)
	{
		(*this) = aVectorOnStack;
	}

	template <typename Type, int Capacity, typename CountType, bool UseSafeModeFlag>
	VectorOnStack<Type, Capacity, CountType, UseSafeModeFlag>::~VectorOnStack()
	{
		mySize = 0;
		myEnd = 0;
	}

	template <typename Type, int Capacity, typename CountType, bool UseSafeModeFlag>
	VectorOnStack<Type, Capacity, CountType, UseSafeModeFlag> &  VectorOnStack<Type, Capacity, CountType, UseSafeModeFlag>::operator=(const VectorOnStack & aVectorOnStack)
	{
		if (UseSafeModeFlag == true)
		{
			for (size_t iSlot = 0; iSlot <= mySize; ++iSlot)
			{
				myData[iSlot] = aVectorOnStack.myData[iSlot];
			}
			myEnd = aVectorOnStack.myEnd;
		}
		else
		{
			memcpy(this, &aVectorOnStack, sizeof(VectorOnStack));
		}
		return (*this);
	}

	

	template <typename Type, int Capacity, typename CountType, bool UseSafeModeFlag>
	const Type& VectorOnStack<Type, Capacity, CountType, UseSafeModeFlag>::operator[](const CountType& aIndex) const
	{
		assert(aIndex < myEnd && "Index is out of range");
		assert(aIndex >= 0 && "Index can not be a negative number");

		return myData[aIndex];
	}

	template <typename Type, int Capacity, typename CountType, bool UseSafeModeFlag>
	Type& VectorOnStack<Type, Capacity, CountType, UseSafeModeFlag>::operator[](const CountType& aIndex)
	{
		assert(aIndex < myEnd && "Index is out of range");
		assert(aIndex >= 0 && "Index can not be a negative number");

		return myData[aIndex];
	}

	template <typename Type, int Capacity, typename CountType, bool UseSafeModeFlag>
	void VectorOnStack<Type, Capacity, CountType, UseSafeModeFlag>::Add(const Type& aObject)
	{
		assert(myEnd <= (mySize) && "Vector is full");

		myData[myEnd] = aObject;
		myEnd++;
	}

	template <typename Type, int Capacity, typename CountType, bool UseSafeModeFlag>
	void VectorOnStack<Type, Capacity, CountType, UseSafeModeFlag>::Insert(CountType aIndex, Type& aObject)
	{
		assert(myEnd <= (mySize) && "Vector is full");
		assert(aIndex <= myEnd && "Index is out of range");
		assert(aIndex >= 0 && "Index can not be a negative number");




		if (aIndex != myEnd)
		{
			for (CountType iData = myEnd; iData > aIndex; --iData)
			{
				myData[iData] = myData[iData - 1];
			}
		}

		myData[aIndex] = aObject;
		++myEnd;
	}

	template <typename Type, int Capacity, typename CountType, bool UseSafeModeFlag>
	void VectorOnStack<Type, Capacity, CountType, UseSafeModeFlag>::DeleteCyclic(Type& aObject)
	{
		assert(myEnd > 0 && "Vector is empty");

		if (myEnd != 1)
		{
			for (CountType iSlot = myEnd - 1; iSlot >= 0; --iSlot)
			{
				if (myData[iSlot] == aObject)
				{
					DeleteCyclicAtIndex(iSlot);
					return;
				}
			}
		}
		else
		{
			if (myData[0] == aObject)
			{
				DeleteCyclicAtIndex(0);
				return;
			}
		}
	}

	template <typename Type, int Capacity, typename CountType, bool UseSafeModeFlag>
	void VectorOnStack<Type, Capacity, CountType, UseSafeModeFlag>::DeleteCyclicAtIndex(CountType aItemNumber)
	{
		assert(aItemNumber < myEnd && "Index is out of range");
		assert(aItemNumber >= 0 && "Index can not be a negative number");

		if (myEnd != 1)
		{
			delete myData[aItemNumber];
			myData[aItemNumber] = myData[myEnd - 1];
			--myEnd;
		}
		else
		{
			delete myData[0];
			Clear();
		}
	}

	template <typename Type, int Capacity, typename CountType, bool UseSafeModeFlag>
	void VectorOnStack<Type, Capacity, CountType, UseSafeModeFlag>::RemoveCyclic(const Type& aObject)
	{
		assert(myEnd > 0 && "Vector is empty");

		if (myEnd != 1)
		{
			for (CountType iSlot = 0; iSlot < myEnd; ++iSlot)
			{
				if (myData[iSlot] == aObject)
				{
					RemoveCyclicAtIndex(iSlot);
					return;
				}
			}
		}
		else
		{
			if (myData[0] == aObject)
			{
				RemoveCyclicAtIndex(0);
				return;
			}
		}
	}
	
	template <typename Type, int Capacity, typename CountType, bool UseSafeModeFlag>
	void VectorOnStack<Type, Capacity, CountType, UseSafeModeFlag>::RemoveCyclicAtIndex(CountType aItemNumber)
	{
		assert(aItemNumber < myEnd && "Index is out of range");
		assert(aItemNumber >= 0 && "Index can not be a negative number");

		if (myEnd != 1)
		{
			myData[aItemNumber] = myData[myEnd - 1];
			--myEnd;
		}
		else
		{
			Clear();
		}
	}

	template <typename Type, int Capacity, typename CountType, bool UseSafeModeFlag>
	void VectorOnStack<Type, Capacity, CountType, UseSafeModeFlag>::DeleteAll()
	{
		for (size_t iSlot = 0; iSlot < myEnd; ++iSlot)
		{
			delete myData[iSlot];
			myData[iSlot] = nullptr;
		}
	}

	template <typename Type, int Capacity, typename CountType, bool UseSafeModeFlag>
	void VectorOnStack<Type, Capacity, CountType, UseSafeModeFlag>::Clear()
	{
		myEnd = 0;
	}

	template <typename Type, int Capacity, typename CountType, bool UseSafeModeFlag>
	CountType VectorOnStack<Type, Capacity, CountType, UseSafeModeFlag>::Size() const
	{
		return myEnd;
	}
}