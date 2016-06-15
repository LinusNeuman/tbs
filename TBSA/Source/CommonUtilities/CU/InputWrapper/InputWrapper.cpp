#include "stdafx.h"
#include "InputWrapper.h"
#include <amp.h>


namespace CommonUtilities
{

	InputWrapper::InputWrapper()
	{
		myKeyboardData.resize(256);
		myPreviousKeyboardData.resize(256);
		myImInitialized = false;
	}


	InputWrapper::~InputWrapper()
	{
		myKeyboard->Unacquire();
		myKeyboard->Release();
		myKeyboard = nullptr;

		myMouse->Unacquire();
		myMouse->Release();
		myMouse = nullptr;

		myInputInterface->Release();
		myInputInterface = nullptr;
	}


	void InputWrapper::Initialize(HINSTANCE aApplicationInstance, HWND aWindow)
	{
		HRESULT inputError;
		inputError = DirectInput8Create(aApplicationInstance, DIRECTINPUT_VERSION, IID_IDirectInput8A, reinterpret_cast<void**>(&myInputInterface), nullptr);

		myWindowID = aWindow;

		myInputInterface->CreateDevice(GUID_SysKeyboard, &myKeyboard, nullptr);
		myInputInterface->CreateDevice(GUID_SysMouse, &myMouse, nullptr);

		myKeyboard->SetDataFormat(&c_dfDIKeyboard);
		myKeyboard->SetCooperativeLevel(aWindow, DISCL_BACKGROUND);
		myKeyboard->Acquire();

		myMouse->SetDataFormat(&c_dfDIMouse);
		myMouse->SetCooperativeLevel(aWindow, DISCL_BACKGROUND);
		myMouse->Acquire();

		myImInitialized = true;
	}

	void InputWrapper::Update()
	{
		if (myImInitialized == false)
		{
			return;
		}

		CU::Vector2f tempPosition = GetMouseWindowPositionNormalizedSpace();

		if (tempPosition.x > 1.f || tempPosition.x < 0.f ||
			tempPosition.y > 1.f || tempPosition.y < 0.f)
		{
			if ((CU::WindowsFunctions::CheckIfWindowFullscreen(myWindowID)) == true)
			{
				CU::Point2ui newPosition(tempPosition.x, tempPosition.y);

				tempPosition.x = min(1.f, max(tempPosition.x, 0.f));
				tempPosition.y = min(1.f, max(tempPosition.y, 0.f));

				RECT tempWindow;
				GetClientRect(myWindowID, &tempWindow);

				//newPosition.x = newPosition.x * tempWindow.right;
				//newPosition.y = newPosition.y * tempWindow.bottom;
				newPosition.x = tempPosition.x * tempWindow.right -4;
				newPosition.y = tempPosition.y * tempWindow.bottom;

				POINT tempPoint;
				tempPoint.x = newPosition.x;
				tempPoint.y = newPosition.y;
				
				ClientToScreen(myWindowID, &tempPoint);

				SetCursorPosition(tempPoint.x, tempPoint.y);
			}
			else
			{
				if (GetActiveWindow() == myWindowID)
				{
					return;
				}
			}
		}


		myPreviousMouseData = myMouseData;
		myMouse->GetDeviceState(sizeof(DIMOUSESTATE), static_cast<LPVOID>(&myMouseData));

		myPreviousKeyboardData = myKeyboardData;
		myKeyboard->GetDeviceState(sizeof(BYTE) * myKeyboardData.size(), static_cast<void*>(&myKeyboardData[0]));
	}

}