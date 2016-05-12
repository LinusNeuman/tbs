#pragma once
#include "BaseMessage.h"
#include <CU/NameSpaceAliases.h>
#include <CU/Vectors/vector4.h>

struct WindowRectChangedMessage : public BaseMessage
{
	WindowRectChangedMessage(const RecieverTypes aRecieverType, const float aXpos, const float aYpos, const float aWidth, const float aHeight,
		const long aWindowXPos, const long aWindowYPos,
		const long aWindowRightXPos, const long aWindowRightYPos)
		: BaseMessage(aRecieverType),
		myViewPortRect(aXpos, aYpos, aWidth, aHeight),
		myWindowRect(static_cast<float>(aWindowXPos), static_cast<float>(aWindowYPos), static_cast<float>(aWindowRightXPos), static_cast<float>(aWindowRightYPos))
	{}

	const CU::Vector4f myViewPortRect;
	const CU::Vector4f myWindowRect;
};