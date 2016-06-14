#pragma once
#pragma comment (lib, "dinput8.lib")
#pragma comment (lib, "dxguid.lib")

#include <dinput.h>
#include <vector>
#include "CU/Utility/WindowsFunctions.h"
#include "CU/DLDebug/DL_Debug.h"
#include "CU/NameSpaceAliases.h"
#include "CU/Vectors/vector2.h"
#include "CU/InputWrapper/MouseButtonsEnum.h"
#include "CU/Utility/CommonCasts.h"



namespace CommonUtilities
{
	class InputWrapper
	{
	public:
		InputWrapper();
		~InputWrapper();

		void Initialize(HINSTANCE aApplicationInstance, HWND aWindow);

		void Update();

		inline LONG GetMouseDeltaX() const;
		inline LONG GetMouseDeltaY() const;
		inline LONG GetWheelDelta() const;

		inline bool GetMouseButtonDown(enumMouseButtons aButton) const;
		inline bool GetMouseButtonReleased(enumMouseButtons aButton) const;
		inline bool GetMouseButtonPressed(enumMouseButtons aButton) const;

		inline bool GetAnyMouseButtonDown() const;
		inline bool GetAnyMouseButtonReleased() const;
		inline bool GetAnyMouseButtonPressed() const;

		inline bool GetKeyDown(int aButton) const;
		inline bool GetKeyPressed(int aButton) const;
		inline bool GetKeyReleased(int aButton) const;

		inline bool GetAnyKeyDown() const;
		inline bool GetAnyKeyPressed() const;
		inline bool GetAnyKeyReleased() const;


		inline void SetCursorPosition(int aXPosition, int aYPosition) const;

		inline LONG GetMouseAbsolutePositionX() const;
		inline LONG GetMouseAbsolutePositionY() const;

		inline Vector2f GetMouseWindowPosition() const;

		inline Vector2f GetMouseWindowPositionNormalizedSpace() const;

		inline void ResetInput();

	private:
		LPDIRECTINPUT8 myInputInterface;
		LPDIRECTINPUTDEVICE8 myKeyboard;
		LPDIRECTINPUTDEVICE8 myMouse;

		std::vector<BYTE> myKeyboardData;
		std::vector<BYTE> myPreviousKeyboardData;

		DIMOUSESTATE myMouseData;
		DIMOUSESTATE myPreviousMouseData;

		HWND myWindowID;
		bool myImInitialized;
	};


	LONG InputWrapper::GetMouseDeltaX() const
	{
		return myMouseData.lX;
	}

	LONG InputWrapper::GetMouseDeltaY() const
	{
		return myMouseData.lY;
	}

	LONG InputWrapper::GetWheelDelta() const
	{
		return myMouseData.lZ;
	}

	bool InputWrapper::GetMouseButtonDown(enumMouseButtons aButton) const
	{
		return (myMouseData.rgbButtons[static_cast<int>(aButton)] > 0);
	}

	bool InputWrapper::GetMouseButtonReleased(enumMouseButtons aButton) const
	{
		return (myPreviousMouseData.rgbButtons[static_cast<int>(aButton)] > 0) && (!(myMouseData.rgbButtons[static_cast<int>(aButton)] > 0));
	}

	bool InputWrapper::GetMouseButtonPressed(enumMouseButtons aButton) const
	{
		return static_cast<bool>(!(myPreviousMouseData.rgbButtons[static_cast<int>(aButton)] > 0)) && (myMouseData.rgbButtons[static_cast<int>(aButton)] > 0);
	}



	bool InputWrapper::GetKeyDown(int aButton) const
	{
		return myKeyboardData[aButton] > 0;
	}


	bool InputWrapper::GetKeyPressed(int aButton) const
	{
		return (myKeyboardData[aButton] > 0 && myPreviousKeyboardData[aButton] == 0);
	}

	bool InputWrapper::GetKeyReleased(int aButton) const
	{
		return (myKeyboardData[aButton] == 0 && myPreviousKeyboardData[aButton] > 0);
	}

	void InputWrapper::SetCursorPosition(int aXPosition, int aYPosition) const
	{
		SetCursorPos(aXPosition, aYPosition);
	}

	LONG InputWrapper::GetMouseAbsolutePositionX() const
	{
		POINT tempPoint;
		GetCursorPos(&tempPoint);
		return tempPoint.x;
	}

	LONG InputWrapper::GetMouseAbsolutePositionY() const
	{
		POINT tempPoint;
		GetCursorPos(&tempPoint);
		return tempPoint.y;
	}

	inline Vector2f InputWrapper::GetMouseWindowPosition() const
	{
		POINT tempPoint;
		GetCursorPos(&tempPoint);

		ScreenToClient(myWindowID, &tempPoint);

		/*RECT tempWindow;
		GetClientRect(myWindowID, &tempWindow);*/

		return Vector2f(static_cast<float>(tempPoint.x), static_cast<float>(tempPoint.y));
	}

	inline Vector2f InputWrapper::GetMouseWindowPositionNormalizedSpace() const
	{
		POINT tempPoint;
		GetCursorPos(&tempPoint);

		ScreenToClient(myWindowID, &tempPoint);

		RECT tempWindow;
		GetClientRect(myWindowID, &tempWindow);

		return Vector2f((static_cast<float>(tempPoint.x) / static_cast<float>(tempWindow.right)), (static_cast<float>(tempPoint.y) / static_cast<float>(tempWindow.bottom)));
	}

	inline void InputWrapper::ResetInput()
	{
		myKeyboardData.clear();
		myPreviousKeyboardData.clear();
		
		myKeyboardData.resize(256);
		myPreviousKeyboardData.resize(256);

		/*
			CLEAR MOUSE BUFFERS
		*/
	}

	inline bool InputWrapper::GetAnyKeyDown() const
	{
		for (unsigned short iKey = 0; iKey < myKeyboardData.size(); ++iKey)
		{
			if (GetKeyDown(iKey) == true)
			{
				return true;
			}
		}
		return false;
	}

	inline bool InputWrapper::GetAnyKeyPressed() const
	{
		for (unsigned short iKey = 0; iKey < myKeyboardData.size(); ++iKey)
		{
			if (GetKeyPressed(iKey) == true)
			{
				return true;
			}
		}
		return false;
	}

	inline bool InputWrapper::GetAnyKeyReleased() const
	{
		for (unsigned short iKey = 0; iKey < myKeyboardData.size(); ++iKey)
		{
			if (GetKeyReleased(iKey) == true)
			{
				return true;
			}
		}
		return false;
	}

	bool InputWrapper::GetAnyMouseButtonDown() const
	{
		for (unsigned short iMouseButton = 0; iMouseButton < USHORTCAST(enumMouseButtons::enumLength); ++iMouseButton)
		{
			if (GetMouseButtonDown(static_cast<enumMouseButtons>(iMouseButton)) == true)
			{
				return true;
			}
		}
		return false;
	}

	bool InputWrapper::GetAnyMouseButtonReleased() const
	{
		for (unsigned short iMouseButton = 0; iMouseButton < USHORTCAST(enumMouseButtons::enumLength); ++iMouseButton)
		{
			if (GetMouseButtonReleased(static_cast<enumMouseButtons>(iMouseButton)) == true)
			{
				return true;
			}
		}
		return false;
	}

	bool InputWrapper::GetAnyMouseButtonPressed() const
	{
		for (unsigned short iMouseButton = 0; iMouseButton < USHORTCAST(enumMouseButtons::enumLength); ++iMouseButton)
		{
			if (GetMouseButtonPressed(static_cast<enumMouseButtons>(iMouseButton)) == true)
			{
				return true;
			}
		}
		return false;
	}
}