#pragma once
#include <queue>
#include "../GrowingArray/GrowingArray.h"

namespace CommonUtilities
{
	template<typename T, int Size = 10>
	class MemoryPool
	{
	public:
		MemoryPool()
		{
			myObjectList.Init(Size);
			for (unsigned short i = 0; i < Size; i++)
			{
				myObjectList.Add(T());
				myFreeObjects.push(&myObjectList[i]);
			}
		}
#undef GetObject
		T* GetObject()
		{
			T* tempObject = myFreeObjects.front();
			myFreeObjects.pop();
			return tempObject;
		}
		void RecycleObject(T* aObject)
		{
			myFreeObjects.push(aObject);
		}
	private:
		GrowingArray<T> myObjectList;
		std::queue<T*> myFreeObjects;
	};
}
