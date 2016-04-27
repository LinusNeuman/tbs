#pragma once
#include <queue>
#include <CU/GrowingArray/GrowingArray.h>

template<typename T, int Size>
class MemoryPool
{
public:
	MemoryPool()
	{
		myObjectList.Init(Size);
		for (size_t i = 0; i < Size; i++)
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
	CommonUtilities::GrowingArray<T> myObjectList;
	std::queue<T*> myFreeObjects;
};
