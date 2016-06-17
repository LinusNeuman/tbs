#pragma once

namespace DX2D
{
	template<class TYPE>
	struct SSimplePointerArray
	{
		SSimplePointerArray() :myData(nullptr), myNextCount(-1), mySize(0){}
		~SSimplePointerArray()
		{
			delete[] myData;
		}


		void Init(int aSize)
		{
			myNextCount = -1;
			mySize = aSize;
			myData = new TYPE[aSize];
		}

		TYPE GetAt(int index)
		{
			return myData[index];
		}
		TYPE GetCurrent()
		{
			if (myNextCount < 0 || myNextCount > mySize)
			{
				return nullptr;
			}
			return myData[myNextCount];
		}
		TYPE GetNext()
		{
			myNextCount++;
			if (myNextCount > mySize-1)
			{
				return nullptr;
			}
			return myData[myNextCount];
		}

		void ResetCount()
		{
			myNextCount = -1;
		}

		int NextCount(){ return myNextCount; }
		int TotalCount(){ return mySize; }

		TYPE *myData;
		int myNextCount;
		int mySize;
	};
}