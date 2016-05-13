#include "stdafx.h"
#include "SingletonIsometricInputWrapper.h"
#include <CU/Camera/Camera2D.h>
#include <SingletonPostMaster.h>
#include <CU/Utility/Math/Isometric.h>
#include <Message/WindowRectChangedMessage.h>


SingletonIsometricInputWrapper * SingletonIsometricInputWrapper::ourInstance = nullptr;


void SingletonIsometricInputWrapper::Create(/*const CU::Camera2D & aCameraToAdjustInputToo*/)
{
	if (ourInstance == nullptr)
	{
		ourInstance = new SingletonIsometricInputWrapper(/*aCameraToAdjustInputToo*/);
	}
}


void SingletonIsometricInputWrapper::Destroy()
{
	delete ourInstance;

	ourInstance = nullptr;
}


SingletonIsometricInputWrapper::SingletonIsometricInputWrapper(/*const CU::Camera2D & aCameraToAdjustInputToo*/)
{
	SingletonPostMaster::AddReciever(RecieverTypes::eWindowProperties, *this);
}


SingletonIsometricInputWrapper::~SingletonIsometricInputWrapper()
{
	SingletonPostMaster::RemoveReciever(RecieverTypes::eWindowProperties, *this);
}

CU::Vector2f SingletonIsometricInputWrapper::ConvertMouseNormalizedPositionCartesianCordiante() const
{

	CU::Vector2f mousePosition = GetMouseInViewportNormalized();

	mousePosition.x = mousePosition.x * (1920.f);
	mousePosition.y = mousePosition.y * (1080.f);

	return mousePosition;
}

CU::Vector2f SingletonIsometricInputWrapper::GetMouseWindowPositionIsometric()
{
	CU::Vector2f mousePosition = GetInstance().ConvertMouseNormalizedPositionCartesianCordiante();

	CU::Vector2f tempOffset(550.f, 250.f);
	mousePosition -= tempOffset;

	CU::Vector2f newPos = CU::PixelToIsometric(mousePosition);

	return newPos;
}

CU::Vector2f SingletonIsometricInputWrapper::GetMouseInViewportNormalized() const
{
	CU::Vector2f mousePosition = myInputWrapper.GetMouseWindowPosition();

	mousePosition.x -= myViewPortSettings.x;
	mousePosition.y -= myViewPortSettings.y;

	mousePosition.x /= (myWindowRect.z - (myViewPortSettings.x * 2.f));
	mousePosition.y /= (myWindowRect.w - (myViewPortSettings.y * 2.f));

	return mousePosition;
}

void SingletonIsometricInputWrapper::Initialize(HINSTANCE aApplicationInstance, HWND aWindow)
{
	GetInstance().myInputWrapper.Initialize(aApplicationInstance, aWindow);
}

void SingletonIsometricInputWrapper::Update()
{
	GetInstance().myInputWrapper.Update();
}

void SingletonIsometricInputWrapper::RecieveMessage(const WindowRectChangedMessage & aMessage)
{
	myViewPortSettings = aMessage.myViewPortRect;
	myWindowRect = aMessage.myWindowRect;
}