#pragma once
#include <CU/InputWrapper/InputWrapper.h>
#include <PostMaster/MessageReceiver.h>
//


class Camera2D;


class SingletonIsometricInputWrapper : public MessageReciever
{
public:
	static void Create();
	static void Destroy();

	static void Initialize(HINSTANCE aApplicationInstance, HWND aWindow);

	static void Update();

	inline static LONG GetMouseDeltaX();
	inline static LONG GetMouseDeltaY();
	inline static LONG GetWheelDelta();

	inline static bool GetMouseButtonDown(CommonUtilities::enumMouseButtons aButton);
	inline static bool GetMouseButtonReleased(CommonUtilities::enumMouseButtons aButton);
	inline static bool GetMouseButtonPressed(CommonUtilities::enumMouseButtons aButton);

	inline static bool GetKeyDown(int aButton);
	inline static bool GetKeyPressed(int aButton);
	inline static bool GetKeyReleased(int aButton);

	inline static void SetCursorPosition(int aXPosition, int aYPosition);

	inline static LONG GetMouseAbsolutePositionX();
	inline static LONG GetMouseAbsolutePositionY();

	inline static CU::Vector2f GetMouseWindowPosition();

	inline static CU::Vector2f GetMouseWindowPositionNormalizedSpace();
	static CU::Vector2f GetMouseWindowPositionIsometric();

	inline static void ResetInput();

	inline static void SetViewPortSettings(const CU::Vector4f & aViewPortStats);

	virtual void RecieveMessage(const WindowRectChangedMessage & aMessage) override;
	virtual void RecieveMessage(const SetMainCameraMessage & aMessage) override;


private:
	SingletonIsometricInputWrapper();
	~SingletonIsometricInputWrapper();

	CU::Vector2f ConvertMouseNormalizedPositionCartesianCordiante(const bool aOffsetToMiddle = false) const;
	CU::Vector2f GetMouseInViewportNormalized() const;

	static SingletonIsometricInputWrapper* ourInstance;
	inline static SingletonIsometricInputWrapper & GetInstance();

	CU::Vector4f myViewPortSettings;
	CU::Vector4f myWindowRect;

	CommonUtilities::InputWrapper myInputWrapper;
	const Camera2D * myCameraToAdjustTo;
};

inline SingletonIsometricInputWrapper & SingletonIsometricInputWrapper::GetInstance()
{
	DL_ASSERT(ourInstance != nullptr, "InputWrapper Instance is nullptr");
	return (*ourInstance);
}

inline  LONG SingletonIsometricInputWrapper::GetMouseDeltaX()
{
	return GetInstance().myInputWrapper.GetMouseDeltaX();
}

inline LONG SingletonIsometricInputWrapper::GetMouseDeltaY()
{
	return GetInstance().myInputWrapper.GetMouseDeltaY();
}


inline LONG SingletonIsometricInputWrapper::GetWheelDelta()
{
	return GetInstance().myInputWrapper.GetWheelDelta();
}


/*
	returns true if was button is on this frame.
*/
inline bool SingletonIsometricInputWrapper::GetMouseButtonDown(CommonUtilities::enumMouseButtons aButton)
{
	return GetInstance().myInputWrapper.GetMouseButtonDown(aButton);
}

/*
	returns true if button was off last frame and on this frame;
*/
inline bool SingletonIsometricInputWrapper::GetMouseButtonReleased(CommonUtilities::enumMouseButtons aButton)
{
	return GetInstance().myInputWrapper.GetMouseButtonReleased(aButton);
}

/*
	returns true if button was on last frame and off this frame;
*/
inline bool SingletonIsometricInputWrapper::GetMouseButtonPressed(CommonUtilities::enumMouseButtons aButton)
{
	return GetInstance().myInputWrapper.GetMouseButtonPressed(aButton);
}

/*
	returns true if key is on this frame.
*/
inline bool SingletonIsometricInputWrapper::GetKeyDown(int aButton)
{
	return GetInstance().myInputWrapper.GetKeyDown(aButton);
}

/*
	returns true if key was off last frame and on this frame;
*/
inline bool SingletonIsometricInputWrapper::GetKeyPressed(int aButton)
{
	return GetInstance().myInputWrapper.GetKeyPressed(aButton);
}

/*
	returns true if key was on last frame and off this frame;
*/
inline bool SingletonIsometricInputWrapper::GetKeyReleased(int aButton)
{
	return GetInstance().myInputWrapper.GetKeyReleased(aButton);
}

inline void SingletonIsometricInputWrapper::SetCursorPosition(int aXPosition, int aYPosition)
{
	return GetInstance().myInputWrapper.SetCursorPosition(aXPosition, aYPosition);
}

inline LONG SingletonIsometricInputWrapper::GetMouseAbsolutePositionX()
{
	return GetInstance().myInputWrapper.GetMouseAbsolutePositionX();
}

inline LONG SingletonIsometricInputWrapper::GetMouseAbsolutePositionY()
{
	return GetInstance().myInputWrapper.GetMouseAbsolutePositionY();
}

inline CU::Vector2f SingletonIsometricInputWrapper::GetMouseWindowPosition()
{
	//return GetInstance().myInputWrapper.GetMouseWindowPosition();
	return GetInstance().ConvertMouseNormalizedPositionCartesianCordiante();
}

inline CU::Vector2f SingletonIsometricInputWrapper::GetMouseWindowPositionNormalizedSpace()
{
	//return GetInstance().myInputWrapper.GetMouseWindowPositionNormalizedSpace();
	return GetInstance().GetMouseInViewportNormalized();
}

void SingletonIsometricInputWrapper::SetViewPortSettings(const CU::Vector4f & aViewPortStats)
{
	GetInstance().myViewPortSettings = aViewPortStats;
}

/*
	clears the input buffer for the keyboard. TODO is for mouse also.
*/
void SingletonIsometricInputWrapper::ResetInput()
{
	GetInstance().myInputWrapper.ResetInput();
}


typedef SingletonIsometricInputWrapper IsometricInput;
