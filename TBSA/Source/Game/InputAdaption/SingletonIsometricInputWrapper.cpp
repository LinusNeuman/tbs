#include "stdafx.h"
//#include "SingletonIsometricInputWrapper.h"
//#include <Camera/Camera2D.h>
//#include <Isometric/IsometricConversion.h>
//#include <Renderer.h>
//#include <SingletonPostMaster.h>
//#include <tga2d/engine.h>
//
//SingletonIsometricInputWrapper * SingletonIsometricInputWrapper::ourInstance = nullptr;
//
//
//
//
//void SingletonIsometricInputWrapper::RecieveMessage(const Message & aMessageToRecieve)
//{
//	throw std::logic_error("The method or operation is not implemented.");
//}
//
//void SingletonIsometricInputWrapper::Create(const Camera2D & aCameraToAdjustInputToo)
//{
//	if (ourInstance == nullptr)
//	{
//		ourInstance = new SingletonIsometricInputWrapper(aCameraToAdjustInputToo);
//	}
//}
//
//
//void SingletonIsometricInputWrapper::Destroy()
//{
//	delete ourInstance;
//
//	ourInstance = nullptr;
//}
//
//
//SingletonIsometricInputWrapper::SingletonIsometricInputWrapper(const Camera2D & aCameraToAdjustInputToo)
//{
//	myCameraToAdjustTo = &aCameraToAdjustInputToo;
//
//	myViewPortSettings.x = 0.f;
//	myViewPortSettings.y = 0.f;
//	myViewPortSettings.z = aCameraToAdjustInputToo.GetScreenResolution().x;
//	myViewPortSettings.w = aCameraToAdjustInputToo.GetScreenResolution().y;
//
//	SingletonPostMaster::AddReciever(RecieverTypes::eWindowProperties, *this);
//}
//
//
//SingletonIsometricInputWrapper::~SingletonIsometricInputWrapper()
//{
//	SingletonPostMaster::RemoveReciever(RecieverTypes::eWindowProperties, *this);
//}
//
//Vector2f SingletonIsometricInputWrapper::ConvertMouseNormalizedPositionCartesianCordiante() const
//{
//
//	Vector2f mousePosition = GetMouseInViewportNormalized();
//
//	mousePosition.x -= 0.5f;
//	mousePosition.y -= 0.5f;
//
//	mousePosition.x = mousePosition.x * (1920.f / 1.5f);
//	mousePosition.y = mousePosition.y * (1080.f / 1.5f);
//	
//	mousePosition = IsometricToCartesian(mousePosition);
//	mousePosition = PixelCordinateToTileCordinate(mousePosition);
//	
//
//	mousePosition = GetInstance().myCameraToAdjustTo->GetPosition() + mousePosition;
//
//	return mousePosition;
//}
//
//Vector2f SingletonIsometricInputWrapper::GetMouseInViewportNormalized() const
//{
//	RECT r;
//	GetClientRect(*DX2D::CEngine::GetInstance()->GetHWND(), &r);
//
//	Vector2f mousePosition = myInputWrapper.GetMouseWindowPosition();
//
//	mousePosition.x -= myViewPortSettings.x;
//	mousePosition.y -= myViewPortSettings.y;
//
//	mousePosition.x /= (r.right - (myViewPortSettings.x * 2.f));
//	mousePosition.y /= (r.bottom - (myViewPortSettings.y * 2.f));
//
//	return mousePosition;
//}
//
//void SingletonIsometricInputWrapper::Initialize(HINSTANCE aApplicationInstance, HWND aWindow)
//{
//	GetInstance().myInputWrapper.Initialize(aApplicationInstance, aWindow);
//}
//
//void SingletonIsometricInputWrapper::Update()
//{
//	GetInstance().myInputWrapper.Update();
//}