#pragma once
#include "../GrowingArray/GrowingArray.h"
#include "../DLDebug/DL_Debug.h"
#include "Greater.h"

namespace CommonUtilities
{
	template <typename T, typename TComparer = Greater<T>>
	class Heap
	{
	public:

		Heap();
		Heap(const CommonUtilities::GrowingArray<T> & aGrowingArray);
		void Enqueue(T someData);
		T Dequeue();
		bool IsEmpty();

		bool IsHeap();
		bool IsHeap(const CommonUtilities::GrowingArray<T> & aGrowingArray);

		const T & Peek();
		void ClearAndSort(const CommonUtilities::GrowingArray<T> & aGrowingArray);
		void Resort();

		void DeleteAll();
		void RemoveAll();

	private:
		GrowingArray<T> myData;
		TComparer myComparer;

		void Climb(unsigned short anIndex);
		void Drop(unsigned short anIndex);
		bool TraverseCheckIsHeap(const CommonUtilities::GrowingArray<T> & aGrowingArray, unsigned short anIndex);
	};

	template <typename T, typename TComparer /*= Greater<T>*/>
	void CommonUtilities::Heap<T, TComparer>::Resort()
	{
		for (unsigned short i = static_cast<unsigned short>(static_cast<float>(myData.Size()) / 2.f - 0.5f); i < myData.Size(); --i)
		{
			Drop(i);
		}
	}

	template <typename T, typename TComparer /*= Greater<T>*/>
	CommonUtilities::Heap<T, TComparer>::Heap(const CommonUtilities::GrowingArray<T> & aGrowingArray)
	{
		myData.Init(1);
		ClearAndSort(aGrowingArray);		
	}

	template <typename T, typename TComparer /*= Greater<T>*/>
	CommonUtilities::Heap<T, TComparer>::Heap()
	{
		myData.Init(1);
	}

	template <typename T, typename TComparer /*= Greater<T>*/>
	void CommonUtilities::Heap<T, TComparer>::Enqueue(T someData)
	{
		myData.Add(someData);
		Climb(myData.Size() - 1);
	}

	template <typename T, typename TComparer /*= Greater<T>*/>
	T CommonUtilities::Heap<T, TComparer>::Dequeue()
	{
		DL_ASSERT(myData.Size() > 0, "Heap error - Trying to dequeue an empty heap!");
		T temp = myData[0];
		myData.RemoveCyclicAtIndex(0);
		if (myData.Size() > 1)
		{
			Drop(0);
		}
		return temp;
	}

	template <typename T, typename TComparer /*= Greater<T>*/>
	bool CommonUtilities::Heap<T, TComparer>::IsEmpty()
	{
		return (myData.Size() <= 0);
	}

	template <typename T, typename TComparer /*= Greater<T>*/>
	bool CommonUtilities::Heap<T, TComparer>::IsHeap()
	{
		return IsHeap(myData);
	}

	template <typename T, typename TComparer /*= Greater<T>*/>
	bool CommonUtilities::Heap<T, TComparer>::IsHeap(const CommonUtilities::GrowingArray<T> & aGrowingArray)
	{
		if (aGrowingArray.Size() > 0)
		{
			return TraverseCheckIsHeap(aGrowingArray, 0);
		}
		else
		{
			return true;
		}
	}

	template <typename T, typename TComparer /*= Greater<T>*/>
	const T & CommonUtilities::Heap<T, TComparer>::Peek()
	{
		DL_ASSERT(myData.Size() > 0, "Heap error - Trying to peek on an empty heap!");
		return myData[0];
	}

	template <typename T, typename TComparer /*= Greater<T>*/>
	void CommonUtilities::Heap<T, TComparer>::ClearAndSort(const CommonUtilities::GrowingArray<T> & aGrowingArray)
	{
		myData.RemoveAll();
		myData = aGrowingArray;

		Resort();
	}

	template <typename T, typename TComparer /*= Greater<T>*/>
	void CommonUtilities::Heap<T, TComparer>::DeleteAll()
	{
		myData.DeleteAll();
	}


	template <typename T, typename TComparer /*= Greater<T>*/>
	void CommonUtilities::Heap<T, TComparer>::RemoveAll()
	{
		myData.RemoveAll();
	}


	template <typename T, typename TComparer /*= Greater<T>*/>
	void CommonUtilities::Heap<T, TComparer>::Climb(unsigned short anIndex)
	{
		if (anIndex > 0)
		{
			unsigned short parentIndex = (anIndex - 1) / 2;

			if (myComparer(myData[anIndex], myData[parentIndex]) == true)
			{
				std::swap(myData[anIndex], myData[parentIndex]);
				Climb(parentIndex);
			}
		}
	}

	template <typename T, typename TComparer /*= Greater<T>*/>
	void CommonUtilities::Heap<T, TComparer>::Drop(unsigned short anIndex)
	{
		unsigned short firstChildIndex = anIndex * 2 + 1;
		unsigned short secondChildIndex = anIndex * 2 + 2;
		if (firstChildIndex < myData.Size())
		{
			unsigned short greatestChild = firstChildIndex;
			if (secondChildIndex < myData.Size() && myComparer(myData[secondChildIndex], myData[firstChildIndex]) == true)
			{
				greatestChild = secondChildIndex;
			}

			if (myComparer(myData[greatestChild], myData[anIndex]) == true)
			{
				std::swap(myData[greatestChild], myData[anIndex]);
				Drop(greatestChild);
			}
		}
	}


	template <typename T, typename TComparer /*= Greater<T>*/>
	bool CommonUtilities::Heap<T, TComparer>::TraverseCheckIsHeap(const CommonUtilities::GrowingArray<T> & aGrowingArray, unsigned short anIndex)
	{
		unsigned short firstChildIndex = anIndex * 2 + 1;
		unsigned short secondChildIndex = anIndex * 2 + 2;
		if (firstChildIndex < aGrowingArray.Size())
		{
			if (secondChildIndex < myData.Size() == true)
			{
				if (myComparer(aGrowingArray[secondChildIndex], aGrowingArray[anIndex]) == true)
				{
					return false;
				}
				TraverseCheckIsHeap(aGrowingArray, secondChildIndex);
			}

			if (myComparer(aGrowingArray[firstChildIndex], aGrowingArray[anIndex]) == true)
			{
				return false;
			}
			TraverseCheckIsHeap(aGrowingArray, firstChildIndex);
		}
		return true;
	}
}