#pragma once
#include "BaseMessage.h"

class Camera2D;

#pragma warning  (push)
#pragma warning(disable : 4512)
struct SetMainCameraMessage : public BaseMessage
{
	SetMainCameraMessage(const RecieverTypes aType, const Camera2D & aCamera) : myCamera(aCamera), BaseMessage(aType)
	{}

	const Camera2D & myCamera;
};
#pragma warning (pop)