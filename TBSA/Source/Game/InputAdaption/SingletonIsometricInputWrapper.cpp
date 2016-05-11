#include "stdafx.h"
#include "SingletonIsometricInputWrapper.h"
#include <CU/Camera/Camera2D.h>
#include <SingletonPostMaster.h>
//#include <Isometric/IsometricConversion.h>
//#include <Renderer.h>


//
SingletonIsometricInputWrapper * SingletonIsometricInputWrapper::ourInstance = nullptr;




//void SingletonIsometricInputWrapper::RecieveMessage(const Message & aMessageToRecieve)
//{
//	throw std::logic_error("The method or operation is not implemented.");
//}

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
	//myCameraToAdjustTo = &aCameraToAdjustInputToo;

	/*myViewPortSettings.x = 0.f;
	myViewPortSettings.y = 0.f;
	myViewPortSettings.z = aCameraToAdjustInputToo.GetScreenResolution().x;
	myViewPortSettings.w = aCameraToAdjustInputToo.GetScreenResolution().y;*/

	//SingletonPostMaster::AddReciever(RecieverTypes::eWindowProperties, *this);
}


SingletonIsometricInputWrapper::~SingletonIsometricInputWrapper()
{
	SingletonPostMaster::RemoveReciever(RecieverTypes::eWindowProperties, *this);
	//SingletonPostMaster::RemoveReciever(RecieverTypes::eWindowProperties, *this);
}

CU::Vector2f SingletonIsometricInputWrapper::ConvertMouseNormalizedPositionCartesianCordiante() const
{

	CU::Vector2f mousePosition = GetMouseInViewportNormalized();

	/*mousePosition.x -= 0.5f;
	mousePosition.y -= 0.5f;*/

	mousePosition.x = mousePosition.x * (1920.f);
	mousePosition.y = mousePosition.y * (1080.f);

	//mousePosition = IsometricToCartesian(mousePosition);
	//mousePosition = PixelCordinateToTileCordinate(mousePosition);


	//mousePosition = GetInstance().myCameraToAdjustTo->GetPosition() + mousePosition;

	return mousePosition;
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

void SingletonIsometricInputWrapper::RecieveMessage(const WindowRectChangedMessage aMessage)
{
	myViewPortSettings = aMessage.myViewPortRect;
	myWindowRect = aMessage.myWindowRect;
}