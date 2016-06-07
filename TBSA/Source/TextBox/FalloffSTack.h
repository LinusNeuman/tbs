#pragma once

template<typename T, unsigned int S>
class FalloffStack
{
	public:
		FalloffStack();
		~FalloffStack();
		T& operator[](const unsigned int aIndex);
		void Push(T aObject);

	private:
		void PushOff();

		unsigned int mySize;
		T myObjects[S];
};

template<typename T, unsigned int S>
T& FalloffStack<T, S>::operator[](const unsigned int aIndex)
{
	assert(aIndex >= 0 && aIndex < S);

	return myObjects[aIndex];
}

template<typename T, unsigned int S>
FalloffStack<T, S>::FalloffStack()
{
	for (unsigned int i = 0; i < S; ++i)
	{
		myObjects[i] = nullptr;
	}
}

template<typename T, unsigned int S>
FalloffStack<T, S>::~FalloffStack()
{
	for (unsigned int i = 0; i < S; ++i)
	{
		SAFE_DELETE(myObjects[i]);
	}
}

template<typename T, unsigned int S>
void FalloffStack<T, S>::PushOff()
{
	for (unsigned int i = S - 1; i > 0; --i)
	{
		if (i == S - 1)
		{
			SAFE_DELETE(myObjects[i]);
		}

		myObjects[i] = myObjects[i - 1];
	}
}

template<typename T, unsigned int S>
void FalloffStack<T, S>::Push(T aObject)
{
	PushOff();

	myObjects[0] = aObject;
}
