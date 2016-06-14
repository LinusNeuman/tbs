#include "stdafx.h"
#include "SingletonInputWrapper.h"


namespace CommonUtilities
{

	SingletonInputWrapper * SingletonInputWrapper::ourInstance = nullptr;


	void SingletonInputWrapper::Create()
	{
		if (ourInstance == nullptr)
		{
			ourInstance = new SingletonInputWrapper();
		}
	}


	void SingletonInputWrapper::Destroy()
	{
		delete ourInstance;

		ourInstance = nullptr;
	}


	SingletonInputWrapper::SingletonInputWrapper()
	{
	}


	SingletonInputWrapper::~SingletonInputWrapper()
	{
	}

	void SingletonInputWrapper::Initialize(HINSTANCE aApplicationInstance, HWND aWindow)
	{
		if (ourInstance == nullptr)
		{
			Create();
		}
		GetInstance().myInputWrapper.Initialize(aApplicationInstance, aWindow);
	}

	void SingletonInputWrapper::Update()
	{
		GetInstance().myInputWrapper.Update();
	}

}