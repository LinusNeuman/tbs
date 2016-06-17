#pragma once

#include "CU/DLDebug/DL_Debug.h"
#include "CU/GrowingArray/GrowingArray.h"

namespace CommonUtilities
{

	template<typename TYPE, typename SIZE = unsigned short>
	class ObjectQueue
	{
	public:

		inline ObjectQueue();
		inline ObjectQueue(const SIZE aSize);
		inline ~ObjectQueue();

		inline void Init(SIZE aNrOfRecomendedItems);
		inline void ReInit(SIZE aNrOfRecomendedItems);

		inline TYPE& Allocate();
		inline void Deallocate(TYPE& anObject);
		
		inline void Clear();

		inline SIZE Size() const;

		inline const TYPE& operator[](const SIZE anIndex) const;
		inline TYPE& operator[](const SIZE anIndex);

	private:

		GrowingArray<TYPE, SIZE> myObjects;
		GrowingArray<TYPE*, SIZE> myPointers;

		SIZE myListPoint;
		SIZE mySize;

		void InitInternal(SIZE aSize);

	};

	template<typename TYPE, typename SIZE>
	inline ObjectQueue<TYPE, SIZE>::ObjectQueue()
	{
	}
	template<typename TYPE, typename SIZE>
	inline ObjectQueue<TYPE, SIZE>::ObjectQueue(const SIZE aSize)
	{

		Init(aSize);

	}
	template<typename TYPE, typename SIZE>
	inline ObjectQueue<TYPE, SIZE>::~ObjectQueue()
	{

	}

	template<typename TYPE, typename SIZE>
	inline void ObjectQueue<TYPE, SIZE>::Init(SIZE aNrOfRecomendedItems)
	{

		myListPoint = 0;
		mySize = aNrOfRecomendedItems;

		myObjects.Init(aNrOfRecomendedItems);
		myPointers.Init(aNrOfRecomendedItems);

		InitInternal(aNrOfRecomendedItems);

	}
	template<typename TYPE, typename SIZE>
	inline void ObjectQueue<TYPE, SIZE>::ReInit(SIZE aNrOfRecomendedItems)
	{

		myListPoint = 0;
		mySize = aNrOfRecomendedItems;

		myObjects.ReInit(aNrOfRecomendedItems);
		myPointers.ReInit(aNrOfRecomendedItems);
		
		InitInternal(aNrOfRecomendedItems);

	}

	template<typename TYPE, typename SIZE>
	inline TYPE& ObjectQueue<TYPE, SIZE>::Allocate()
	{

		DL_ASSERT(myListPoint < mySize, "Queue overflow!");
		
		return *myPointers[myListPoint++];

	}
	template<typename TYPE, typename SIZE>
	inline void ObjectQueue<TYPE, SIZE>::Deallocate(TYPE& anObject)
	{

		if (myListPoint == 0)
		{
			return;
		}

		bool exists = false;
		SIZE index = 0;

		for (SIZE i = 0; i < myListPoint; ++i)
		{
			if (myPointers[i] == &anObject)
			{
				index = i;
				exists = true;
				break;
			}
		}

		if (exists == false)
		{
			return;
		}

		--myListPoint;

		myPointers[index] = myPointers[myListPoint];
		myPointers[myListPoint] = &anObject;

	}

	template<typename TYPE, typename SIZE>
	inline void ObjectQueue<TYPE, SIZE>::Clear()
	{
		
		myListPoint = 0;

		for (SIZE i = 0; i < mySize; ++i)
		{
			myPointers.Add(&myObjects[i]);
		}

	}

	template<typename TYPE, typename SIZE>
	inline SIZE ObjectQueue<TYPE, SIZE>::Size() const
	{
		return myListPoint;
	}

	template<typename TYPE, typename SIZE>
	inline const TYPE& ObjectQueue<TYPE, SIZE>::operator[](const SIZE anIndex) const
	{
		
		DL_ASSERT(anIndex >= 0 && anIndex < myListPoint, "GrowingArray out of bounds.");
		
		return *myPointers[anIndex];

	}
	template<typename TYPE, typename SIZE>
	inline TYPE& ObjectQueue<TYPE, SIZE>::operator[](const SIZE anIndex)
	{
		
		DL_ASSERT(anIndex >= 0 && anIndex < myListPoint, "GrowingArray out of bounds.");

		return *myPointers[anIndex];

	}

	template<typename TYPE, typename SIZE>
	inline void ObjectQueue<TYPE, SIZE>::InitInternal(SIZE aSize)
	{

		myObjects.Resize(aSize);

		for (SIZE i = 0; i < aSize; ++i)
		{
			myPointers.Add(&myObjects[i]);
		}

	}

}
