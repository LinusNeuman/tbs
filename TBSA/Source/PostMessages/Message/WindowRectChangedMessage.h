#pragma once
#include "BaseMessage.h"
//#include <CU/NameSpaceAliases.h>
#include <CU/Vectors/vector4.h>

struct WindowRectChangedMessage : public BaseMessage
{
	WindowRectChangedMessage(const RecieverTypes aRecieverType, const float aXpos, const float aYpos, const float aWidth, const float aHeight) 
		: BaseMessage(aRecieverType),
		myWindowRect(aXpos, aYpos, aWidth, aHeight)
	{}

	const CommonUtilities::Vector4f myWindowRect;
};