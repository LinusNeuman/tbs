#pragma once

#include "Message/BaseMessage.h"
#include <CU/NameSpaceAliases.h>
#include <CU/Vectors/vector2.h>

#pragma warning  (push)
#pragma warning(disable : 4512)
struct SetTargetResolutionMessage : public BaseMessage
{
	SetTargetResolutionMessage(const RecieverTypes aRecieverType, const CU::Vector2ui & aResolution)
		: BaseMessage(aRecieverType),
		myResolution(aResolution)
	{
	}

	const CU::Vector2ui & myResolution;
};
#pragma warning (pop)