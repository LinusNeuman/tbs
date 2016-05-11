#pragma once
//#include <CU/InputWrapper/InputWrapper.h>
//#include <MessageReciever.h>
//
//
//class Camera2D;
//
//class SingletonIsometricInputWrapper : public MessageReciever
//{
//public:
//	static void Create(const Camera2D & aCameraToAdjustInputToo);
//	static void Destroy();
//
//	static void Initialize(HINSTANCE aApplicationInstance, HWND aWindow);
//
//	static void Update();
//
//	inline static LONG GetMouseDeltaX();
//	inline static LONG GetMouseDeltaY();
//	inline static LONG GetWheelDelta();
//
//	inline static bool GetMouseButtonDown(CommonUtilities::enumMouseButtons aButton);
//	inline static bool GetMouseButtonReleased(CommonUtilities::enumMouseButtons aButton);
//	inline static bool GetMouseButtonPressed(CommonUtilities::enumMouseButtons aButton);
//
//	inline static bool GetKeyDown(int aButton);
//	inline static bool GetKeyPressed(int aButton);
//	inline static bool GetKeyReleased(int aButton);
//
//	inline static void SetCursorPosition(int aXPosition, int aYPosition);
//
//	inline static LONG GetMouseAbsolutePositionX();
//	inline static LONG GetMouseAbsolutePositionY();
//
//	inline static Vector2f GetMouseWindowPosition();
//
//	inline static Vector2f GetMouseWindowPositionNormalizedSpace();
//
//	inline static void SetViewPortSettings(const Vector4f & aViewPortStats);
//
//	virtual void RecieveMessage(const Message & aMessageToRecieve) override;
//
//private:
//	SingletonIsometricInputWrapper(const Camera2D & aCameraToAdjustInputToo);
//	~SingletonIsometricInputWrapper();
//
//	Vector2f ConvertMouseNormalizedPositionCartesianCordiante() const;
//	Vector2f GetMouseInViewportNormalized() const;
//
//	static SingletonIsometricInputWrapper* ourInstance;
//	inline static SingletonIsometricInputWrapper & GetInstance();
//
//	Vector4f myViewPortSettings;
//
//	CommonUtilities::InputWrapper myInputWrapper;
//	const Camera2D * myCameraToAdjustTo;
//};
//
//inline SingletonIsometricInputWrapper & SingletonIsometricInputWrapper::GetInstance()
//{
//	DL_ASSERT(ourInstance != nullptr, "InputWrapper Instance is nullptr");
//	return (*ourInstance);
//}
//
//inline  LONG SingletonIsometricInputWrapper::GetMouseDeltaX()
//{
//	return GetInstance().myInputWrapper.GetMouseDeltaX();
//}
//
//inline LONG SingletonIsometricInputWrapper::GetMouseDeltaY()
//{
//	return GetInstance().myInputWrapper.GetMouseDeltaY();
//}
//
//
//inline LONG SingletonIsometricInputWrapper::GetWheelDelta()
//{
//	return GetInstance().myInputWrapper.GetWheelDelta();
//}
//
//inline bool SingletonIsometricInputWrapper::GetMouseButtonDown(CommonUtilities::enumMouseButtons aButton)
//{
//	return GetInstance().myInputWrapper.GetMouseButtonDown(aButton);
//}
//
//inline bool SingletonIsometricInputWrapper::GetMouseButtonReleased(CommonUtilities::enumMouseButtons aButton)
//{
//	return GetInstance().myInputWrapper.GetMouseButtonReleased(aButton);
//}
//
//
//inline bool SingletonIsometricInputWrapper::GetMouseButtonPressed(CommonUtilities::enumMouseButtons aButton)
//{
//	return GetInstance().myInputWrapper.GetMouseButtonPressed(aButton);
//}
//
//inline bool SingletonIsometricInputWrapper::GetKeyDown(int aButton)
//{
//	return GetInstance().myInputWrapper.GetKeyDown(aButton);
//}
//
//inline bool SingletonIsometricInputWrapper::GetKeyPressed(int aButton)
//{
//	return GetInstance().myInputWrapper.GetKeyPressed(aButton);
//}
//
//inline bool SingletonIsometricInputWrapper::GetKeyReleased(int aButton)
//{
//	return GetInstance().myInputWrapper.GetKeyReleased(aButton);
//}
//
//inline void SingletonIsometricInputWrapper::SetCursorPosition(int aXPosition, int aYPosition)
//{
//	return GetInstance().myInputWrapper.SetCursorPosition(aXPosition, aYPosition);
//}
//
//inline LONG SingletonIsometricInputWrapper::GetMouseAbsolutePositionX()
//{
//	return GetInstance().myInputWrapper.GetMouseAbsolutePositionX();
//}
//
//inline LONG SingletonIsometricInputWrapper::GetMouseAbsolutePositionY()
//{
//	return GetInstance().myInputWrapper.GetMouseAbsolutePositionY();
//}
//
//inline Vector2f SingletonIsometricInputWrapper::GetMouseWindowPosition()
//{
//	//return GetInstance().myInputWrapper.GetMouseWindowPosition();
//	return GetInstance().ConvertMouseNormalizedPositionCartesianCordiante();
//}
//
//inline Vector2f SingletonIsometricInputWrapper::GetMouseWindowPositionNormalizedSpace()
//{
//	//return GetInstance().myInputWrapper.GetMouseWindowPositionNormalizedSpace();
//	return GetInstance().GetMouseInViewportNormalized();
//}
//
//void SingletonIsometricInputWrapper::SetViewPortSettings(const Vector4f & aViewPortStats)
//{
//	GetInstance().myViewPortSettings = aViewPortStats;
//}
//
//
//typedef SingletonIsometricInputWrapper IsometricInput;