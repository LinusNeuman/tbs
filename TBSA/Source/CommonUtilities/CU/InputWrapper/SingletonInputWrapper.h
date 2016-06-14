#pragma once
#pragma comment (lib, "dinput8.lib")
#pragma comment (lib, "dxguid.lib")

#include <dinput.h>
#include <vector>
#include "CU/Utility/WindowsFunctions.h"
#include "CU/DLDebug/DL_Debug.h"

#include "InputWrapper.h"



namespace CommonUtilities
{
	class SingletonInputWrapper
	{
	public:
		static void Create();
		static void Destroy();

		static void Initialize(HINSTANCE aApplicationInstance, HWND aWindow);

		static void Update();

		inline static LONG GetMouseDeltaX();
		inline static LONG GetMouseDeltaY();
		inline static LONG GetWheelDelta();

		inline static bool GetMouseButtonDown(enumMouseButtons aButton);
		inline static bool GetMouseButtonReleased(enumMouseButtons aButton);
		inline static bool GetMouseButtonPressed(enumMouseButtons aButton);

		inline static bool GetKeyDown(int aButton);
		inline static bool GetKeyPressed(int aButton);
		inline static bool GetKeyReleased(int aButton);

		inline static bool GetAnyKeyDown();
		inline static bool GetAnyKeyPressed();
		inline static bool GetAnyKeyReleased();

		inline static void SetCursorPosition(int aXPosition, int aYPosition);

		inline static LONG GetMouseAbsolutePositionX();
		inline static LONG GetMouseAbsolutePositionY();

		inline static Vector2f GetMouseWindowPosition();

		inline static Vector2f GetMouseWindowPositionNormalizedSpace();


	private:
		SingletonInputWrapper();
		~SingletonInputWrapper();

		static SingletonInputWrapper * ourInstance;
		inline static SingletonInputWrapper & GetInstance();

		InputWrapper myInputWrapper;
	};

	inline SingletonInputWrapper & SingletonInputWrapper::GetInstance()
	{
		DL_ASSERT(ourInstance != nullptr, "InputWrapper Instance is nullptr");
		return (*ourInstance);
	}

	inline  LONG SingletonInputWrapper::GetMouseDeltaX()
	{
		return GetInstance().myInputWrapper.GetMouseDeltaX();
	}

	inline LONG SingletonInputWrapper::GetMouseDeltaY()
	{
		return GetInstance().myInputWrapper.GetMouseDeltaY();
	}


	inline LONG SingletonInputWrapper::GetWheelDelta()
	{
		return GetInstance().myInputWrapper.GetWheelDelta();
	}

	inline bool SingletonInputWrapper::GetMouseButtonDown(enumMouseButtons aButton)
	{
		return GetInstance().myInputWrapper.GetMouseButtonDown(aButton);
	}

	inline bool SingletonInputWrapper::GetMouseButtonReleased(enumMouseButtons aButton)
	{
		return GetInstance().myInputWrapper.GetMouseButtonReleased(aButton);
	}


	inline bool SingletonInputWrapper::GetMouseButtonPressed(enumMouseButtons aButton)
	{
		return GetInstance().myInputWrapper.GetMouseButtonPressed(aButton);
	}

	inline bool SingletonInputWrapper::GetKeyDown(int aButton)
	{
		return GetInstance().myInputWrapper.GetKeyDown(aButton);
	}

	inline bool SingletonInputWrapper::GetKeyPressed(int aButton)
	{
		return GetInstance().myInputWrapper.GetKeyPressed(aButton);
	}

	inline bool SingletonInputWrapper::GetKeyReleased(int aButton)
	{
		return GetInstance().myInputWrapper.GetKeyReleased(aButton);
	}

	inline void SingletonInputWrapper::SetCursorPosition(int aXPosition, int aYPosition)
	{
		return GetInstance().myInputWrapper.SetCursorPosition(aXPosition, aYPosition);
	}

	inline LONG SingletonInputWrapper::GetMouseAbsolutePositionX()
	{
		return GetInstance().myInputWrapper.GetMouseAbsolutePositionX();
	}

	inline LONG SingletonInputWrapper::GetMouseAbsolutePositionY()
	{
		return GetInstance().myInputWrapper.GetMouseAbsolutePositionY();
	}

	inline Vector2f SingletonInputWrapper::GetMouseWindowPosition()
	{
		return GetInstance().myInputWrapper.GetMouseWindowPosition();
	}

	inline Vector2f SingletonInputWrapper::GetMouseWindowPositionNormalizedSpace()
	{
		return GetInstance().myInputWrapper.GetMouseWindowPositionNormalizedSpace();
	}

	inline bool SingletonInputWrapper::GetAnyKeyDown()
	{
		return GetInstance().myInputWrapper.GetAnyKeyDown();
	}

	inline bool SingletonInputWrapper::GetAnyKeyPressed()
	{
		return GetInstance().myInputWrapper.GetAnyKeyPressed();
	}

	inline bool SingletonInputWrapper::GetAnyKeyReleased()
	{
		return GetInstance().myInputWrapper.GetAnyKeyReleased();
	}
}

typedef CU::SingletonInputWrapper GetInput;